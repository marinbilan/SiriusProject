#include "EventHandler.h"
// #include "Initiation_Dispatcher.h"


Reactor::EventHandler::EventHandler(int clientId) : m_clientId(clientId)
{
    std::cout << "[Event_Handler] Constructor called" << '\n';

};


Reactor::EventHandler::~EventHandler()
{
    std::cout << "[EventHandler] Destructor called" << std::endl;
}


int Reactor::EventHandler::handle_event(const std::string& eventType)
{
    std::cout << "[EventHandler] handle_event called ..." << '\n';
};


int Reactor::EventHandler::getClientId() const
{
    return m_clientId;
}


std::string Reactor::EventHandler::send()
{
    std::string msg("Sending msg from handler: ");
    std::string retMsg = msg + std::to_string(m_clientId);

    return retMsg;
}


void Reactor::EventHandler::toString()
{

}