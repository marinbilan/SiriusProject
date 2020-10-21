#pragma once
#include "EventHandlerIf.h"
#include "EventHandler.h"

// TODO: Remove this
class EventHandler
{
public:
    EventHandler(int clientId) : m_clientId(clientId)
    {
        std::cout << "EventHandler created. clientId: " << m_clientId << '\n';
    }

    ~EventHandler()
    {
        std::cout << "EventHandler removed. clientId: " << m_clientId << '\n';
    }

    int getClientId() const
    {
        return m_clientId;
    }

    std::string send()
    {
        std::string msg("Sending msg from handler: ");
        std::string retMsg = msg + std::to_string(m_clientId);

        return retMsg;
    }

    void toString()
    {
        std::cout << "EventHandler clientId: " << m_clientId << '\n';
    }

private:
int m_clientId;
};


namespace Reactor
{
class Logging_Acceptor : public  EventHandlerIf
{
public:
	Logging_Acceptor(int id);

    ~Logging_Acceptor();

    // EVENT: ACCEPT_EVENT (adding handler)
    void register_EventHandler(int clientId);

    // EVENT: CLOSE_EVENT (removeing handler)
    void remove_EventHandler(int socketDescriptorId);
 
    // std::vector<EventHandler*>& get_EventHandlerVec();
    std::vector<EventHandler*>& get_Event_HandlerVec();

    // EVENT: read msg
    int handle_event(const std::string& eventType);

    void processMessage(const int clientId, const std::string& incomingMessage);


private:	
int m_id;

std::vector<EventHandler*> m_vecOfEventHandler;
std::vector<EventHandler*> m_vecOfEvent_Handler;
};
} // End of namespace