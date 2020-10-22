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
    // std::cout << "Hello World from projectX!" << "\n";

    // REACTOR
    /*
	Reactor::Logging_Acceptor la(0);

    Reactor::InitiationDispatcher::getInstance().init();
    Reactor::InitiationDispatcher::getInstance().handle_events();
    */

    // FACTORY
    Common::Factory::Factory::getInstance().preInit();
    Common::Factory::Factory::getInstance().createObjects();

    // CMD PROMPT
    Common::CmdPrompt cmd("TestCmd");
    cmd.runCmdPrompt();

    return 0;
}