#pragma once
#include <string.h>
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <vector>

#include <unistd.h> 

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
 
#include <arpa/inet.h> 

#include <errno.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 

#include "LoggingAcceptor.h"

#define TRUE   1  
#define FALSE  0  

#define PORT 8080

/*
Event Types as string
---------------------
    ACCEPT_EVENT
    READ_EVENT
    WRITE_EVENT
    TIMEOUT_EVENT
    SIGNAL_EVENT
    CLOSE_EVENT
*/


namespace Reactor
{
class InitiationDispatcher
{
public:
	static InitiationDispatcher& getInstance()
	{
		static InitiationDispatcher instance;
		return instance;
	}

	~InitiationDispatcher() {};

	InitiationDispatcher(InitiationDispatcher const&) = delete;
	void operator=(InitiationDispatcher const&) = delete;

    // Init everything related to server
    void init()
    {
        std::cout << "[InitiationDispatcher] init everything" << std::endl;
    
        //initialise all client_socket[] to 0 so not checked  
        for (int i = 0; i < max_clients; i++)   
        {   
            client_socket[i] = 0;   
        }   
            
        //create a master socket  
        if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
        {   
            perror("socket failed");   
            exit(EXIT_FAILURE);   
        }   
        
        std::cout << "MASTER_SOCKET_ID: " << master_socket << '\n';

        //set master socket to allow multiple connections ,  
        //this is just a good habit, it will work without this  
        if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )   
        {   
            perror("setsockopt");   
            exit(EXIT_FAILURE);   
        }   
        
        //type of socket created  
        address.sin_family = AF_INET;   
        address.sin_addr.s_addr = INADDR_ANY;   
        address.sin_port = htons(PORT);   

        //bind the socket to localhost port 8080  
        if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)   
        {   
            perror("bind failed");   
            exit(EXIT_FAILURE);   
        }   
        printf("Listener on port %d \n", PORT);   
            
        //try to specify maximum of 3 pending connections for the master socket  
        if (listen(master_socket, 3) < 0)   
        {   
            perror("listen");   
            exit(EXIT_FAILURE);   
        }   
            
        //accept the incoming connection  
        addrlen = sizeof(address); 
    }


    // Entry point into the reactive event loop
    int handle_events()
    {         
    puts("Waiting for connections ...");
         
        while(TRUE)   
        {   
            // [1] clear the socket set  
            FD_ZERO(&readfds);   
        
            // [2] add master socket to set  
            FD_SET(master_socket, &readfds);   
            // max_sd = master_socket;

            // [3] Set child file descriptors to FD_SET (every iteration)
            for(auto s : m_loggingAcceptor->get_Event_HandlerVec())
            {
                sd = s->getClientId();

                // if valid socket descriptor then add to read list  
                if(sd > 0)   
                {
                    FD_SET(sd , &readfds);
                } 
                    
                // Highest file descriptor number, need it for the select function  
                // Changing master socketId all the time
                /*
                if(sd > max_sd)
                {
                    max_sd = sd; 
                } 
                */
            }
        
            // [4] Wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
            std::cout << "Waiting for activity ..." << '\n';
            std::cout << "master socket: " << master_socket << '\n';
            std::cout << "m_loggingAcceptor->get_Event_HandlerVec().size(): " << m_loggingAcceptor->get_Event_HandlerVec().size() << '\n';
            std::cout << "master socket + vec.size() + 1: " << master_socket + m_loggingAcceptor->get_Event_HandlerVec().size() + 1 << '\n';

            int nfds = master_socket + m_loggingAcceptor->get_Event_HandlerVec().size() + 1;
            // activity = select(max_sd + 1 , &readfds , NULL , NULL , NULL);   
            activity = select(nfds, &readfds , NULL , NULL , NULL);  
        
            if ((activity < 0) && (errno!=EINTR))   
            {   
                printf("select error");   
            }   
                
            // [5] If something happened on the master socket, then its an incoming connection  
            if (FD_ISSET(master_socket, &readfds))   
            {   
                std::cout << " >>>> [ EVENT: ACCEPT_EVENT ] <<<< " << '\n';
                if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
                {   
                    perror("accept");   
                    exit(EXIT_FAILURE);   
                }   

                m_loggingAcceptor->register_EventHandler(new_socket);
                // Create handler for each client (client <-> handler)
                // EventHandler* clientHandler = new EventHandler(new_socket);
                
                // Inform user of socket number - used in send and receive commands  
                printf("New connection , socket fd is %d , ip is : %s , port : %d\n", new_socket, inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                // clientHandler->toString();

                // Send new connection greeting message 
                if(send(new_socket, welcomeMessage, strlen(welcomeMessage), 0) != strlen(welcomeMessage) )   
                {   
                    perror("send");   
                }

                // Add hendler in vec of handlers
                // m_vecOfEventHandler.push_back(clientHandler);
            }   

            // Close event or Read event
            for(auto s : m_loggingAcceptor->get_Event_HandlerVec())
            {
                sd = s->getClientId();

                if (FD_ISSET(sd , &readfds))   
                {   
                    // Check if it was for closing, and also read the incoming message  
                    if ((valread = read(sd , buffer, 1024)) <= 0)   
                    {   
                        std::cout << " >>>> [ EVENT: CLOSE_EVENT ] <<<< " << '\n';

                        // Somebody disconnected , get his details and print  
                        getpeername(sd , (struct sockaddr*)&address, (socklen_t*)&addrlen);   
                        printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   

                        // NEW: Remove EventHandler (client) from vector - move this to Logging_Acceptor
                        /*
                        for(auto it = m_loggingAcceptor->get_EventHandlerVec().begin(); it != m_loggingAcceptor->get_EventHandlerVec().end();) 
                        {
                            if( (*it)->getClientId() == sd ) 
                            { 
                                delete *it; 
                                std::cout << "Deleting *it: " << *it << '\n'; 
                                // Delete   
                                it = m_loggingAcceptor->get_EventHandlerVec().erase(it);
                            }
                            else  
                            { 
                                ++it;  
                            } 
                        }     
                        */
                       m_loggingAcceptor->remove_EventHandler(sd);
                    }                    
                    // Echo back the message that came in  
                    else 
                    {  
                        std::cout << " >>>> [ EVENT: READ_EVENT ] <<<< " << '\n'; 
                        std::cout << " msg from clientId: " << sd << " : " << buffer << '\n'; 

                        std::string incomingMessage(buffer);
                        m_loggingAcceptor->processMessage(sd, incomingMessage);

                        // Message from client <-> handler using clientID
                        // TODO - Move this to Logging Acceptor
                        std::string sendMsg = s->send();
                        send(sd, sendMsg.c_str() , strlen(sendMsg.c_str()) , 0 ); 
                    }   
                } 
            }
        }
    }

    void register_Logging_Acceptor(Logging_Acceptor* loggingAcceptor)
    {
        m_loggingAcceptor = loggingAcceptor;
    }

private:	
	// Singleton Factory - Private Constructor
	InitiationDispatcher() 
	{
	};

    int opt = TRUE; 

    int master_socket;
    int addrlen; 
    int new_socket;
    int client_socket[30];
    int max_clients = 30;

    int activity;
    int i; 
    int valread;
    int sd;
    // int max_sd;   
    struct sockaddr_in address;   
         
    char buffer[1025];  //data buffer of 1K 

    // Set of socket descriptors  
    fd_set readfds;   
         
    // Welcome message  
    char* welcomeMessage = "ECHO from multi server";  

    Logging_Acceptor* m_loggingAcceptor;

    // TODO: remove this
    // std::vector<EventHandler*> m_vecOfEventHandler;
};
} // End of namespace