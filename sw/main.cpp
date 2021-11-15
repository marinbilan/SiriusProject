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
#include "ServiceIf.h"
#include "Service0.h"


int main()
{   
    // FACTORY
    Common::Factory::Factory::getInstance().preInit();
    Common::Factory::Factory::getInstance().createObjects();
    Common::Factory::Factory::getInstance().postInit();

    auto ctrl = FACTORY.getControlIf("control_0");
    ctrl->postInit();

    return 0;
}