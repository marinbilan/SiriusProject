#pragma once
#include <string.h>
#include <iostream>
#include <vector>


namespace Reactor
{
class EventHandlerIf
// = TITLE
// Abstract base class that serves as the
// target of the Initiation_Dispatcher.
{
public:
    virtual ~EventHandlerIf() 
    {
        std::cout << "[EventHandlerIf][~EventHandlerIf]" << std::endl;
    }

    virtual int getClientId() const
    {
        return 0;
    }

    // Hook method that is called back by the
    // Initiation_Dispatcher to handle events.
    // virtual int handle_event(const std::string& eventType) = 0;
    // Hook method that returns the underlying
    // I/O Handle.
    // virtual Handle get_handle (void) const = 0;
};
} // End of Namespace