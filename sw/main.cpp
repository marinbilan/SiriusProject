#include <iostream>
#include <memory>

#include "Database.h"
#include "Factory.h"

#include "EventHandlerIf.h"
#include "EventHandler.h"

int main()
{
    std::cout << "Hello World from projectX!" << "\n";

    std::unique_ptr<Reactor::EventHandlerIf> p = std::make_unique<Reactor::EventHandler>(11);
    std::cout << "clientId: " << p->getClientId() << "\n";

    Common::Database database0("testDatabse.txt");
    database0.preInit();

    Common::Factory::Factory::getInstance().preInit();

    return 0;
}