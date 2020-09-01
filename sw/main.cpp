#include <iostream>
#include <memory>

#include "EventHandlerIf.h"
#include "EventHandler.h"

int main()
{
    std::cout << "Hello World from projectX!" << "\n";

    std::unique_ptr<Reactor::EventHandlerIf> p = std::make_unique<Reactor::EventHandler>(11);
    std::cout << "clientId: " << p->getClientId() << "\n";

    return 0;
}