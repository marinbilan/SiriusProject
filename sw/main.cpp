#include <iostream>
#include <memory>
#include <string>

#include "Database.h"
#include "Factory.h"

#include "EventHandlerIf.h"
#include "EventHandler.h"

#include "ControlIf.h"
#include "Control.h"

int main()
{
    std::cout << "Hello World from projectX!" << "\n";

    // REACTOR
    std::unique_ptr<Reactor::EventHandlerIf> p = std::make_unique<Reactor::EventHandler>(11);
    std::cout << "clientId: " << p->getClientId() << "\n";



    // DATABASE - Create DB and store it in Factory
	std::unique_ptr<Common::Database> database = std::make_unique<Common::Database>("sw/_DB/database_0.txt");
	Common::Factory::getInstance().setDatabase(database);


    // FACTORY
    Common::Factory::Factory::getInstance().preInit();
    Common::Factory::Factory::getInstance().createObjects();

    // Services Creation
    //std::string dbPath("Test path");
    //std::string name("Test name");
    //Control::Control cd(dbPath, name);

    //cd.preInitialization();

    return 0;
}