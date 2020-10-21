#include <iostream>
#include <memory>
#include <string>

#include "CommonIf.h"
#include "CmdPrompt.h"

#include "Database.h"
#include "Factory.h"

#include "EventHandlerIf.h"
#include "EventHandler.h"
#include "InitiationDispatcher.h"
#include "LoggingAcceptor.h"

#include "ControlIf.h"
#include "Control.h"

int main()
{
    std::cout << "Hello World from projectX!" << "\n";

    // REACTOR
    // std::unique_ptr<Reactor::EventHandlerIf> p = std::make_unique<Reactor::EventHandler>(11);
    // std::cout << "clientId: " << p->getClientId() << "\n";
	Reactor::Logging_Acceptor la(0);

    Reactor::InitiationDispatcher::getInstance().init();
    Reactor::InitiationDispatcher::getInstance().handle_events();


    // DATABASE - Create DB and store it in Factory
	std::unique_ptr<Common::Database> database = std::make_unique<Common::Database>("sw/_DB/database_0.txt");
	Common::Factory::getInstance().setDatabase(database);

    // FACTORY
    Common::Factory::Factory::getInstance().preInit();
    Common::Factory::Factory::getInstance().createObjects();

    // CMD PROMPT
    Common::CmdPrompt cmd("TestCmd");
    cmd.runCmdPrompt();

    return 0;
}