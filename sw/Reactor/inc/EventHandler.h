#pragma once
#include "EventHandlerIf.h"


namespace Reactor
{
class EventHandler : public  EventHandlerIf
{
public:
	EventHandler(int clientId);

    ~EventHandler();

    int handle_event(const std::string& eventType);

    int getClientId() const;

    std::string send();

    void toString();

private:	
int m_clientId;
};
} // End of namespace
