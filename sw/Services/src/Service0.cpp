// #pragma once
#include "Service0.h"

#include "Factory.h"

#include <chrono>
#include <thread>
#include <functional>
#include <optional>

#include "EventHandlerIf.h"
#include "EventHandler.h"
#include "InitiationDispatcher.h"
#include "LoggingAcceptor.h"


int Service::Service0::layerDepth = 0;


Service::Service0::Service0(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name),
	m_dbPathWithName(dbPath + name + "_")
{
	FACTORY.getLog()->LOGFILE(LOG "Service: " + m_dbPathWithName + " created. [CONSTRUCTOR]");
}


Service::Service0::~Service0()
{
}


void Service::Service0::preInit()
{
	FACTORY.getLog()->LOGFILE(LOG "Service: " + m_name + " preInit");

	// Get params from DB for this instance
}


void Service::Service0::postInit()
{
	FACTORY.getLog()->LOGFILE(LOG m_name + " postInit");

	std::vector<std::string> vecOfChildrenInstances;
	std::string childrenInstances("childrenInstances");
	FACTORY.getDatabase()->getStringsFromDB(m_dbPathWithName + childrenInstances, vecOfChildrenInstances);


	for(auto s : vecOfChildrenInstances)
	{
		FACTORY.getLog()->LOGFILE(LOG m_name + " - try to get instance: " + s + " from ServiceIf container");

		std::shared_ptr<Service::ServiceIf> serviceIfObjectFromDB = FACTORY.getServiceIf(s).value_or(std::make_shared<Service::Service0>("tempDBPath", "notInDB"));

		// If object is found, cast to CommonIf ptr and store in container
		if(!s.compare(serviceIfObjectFromDB->getName()))
		{
			FACTORY.getLog()->LOGFILE(LOG "Children of " + m_name + " instance: " + serviceIfObjectFromDB->getName());

			std::shared_ptr<Common::CommonIf> commonServiceIf = std::dynamic_pointer_cast<Common::CommonIf>(serviceIfObjectFromDB);
			// commonServiceIf->testMethod();

			// m_vecOfCommonIf.push_back(commonServiceIf);
			m_vecChildCommands.push_back(commonServiceIf);
		}
	}




	/*while(1) 
    {
        std::cout << " print from postInit ... " << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }*/

	// REACTOR
	//Reactor::Logging_Acceptor la(0);
    //Reactor::InitiationDispatcher::getInstance().init();
    //Reactor::InitiationDispatcher::getInstance().handle_events();
}


void Service::Service0::testMethod()
{
	std::cout << "xxxx service name: " << m_name << '\n';
	FACTORY.getLog()->LOGFILE(LOG m_name + " - call from testMethod()");
}

void Service::Service0::dump()
{
    std::cout << " Service DbPathWithName: " << m_dbPathWithName << '\n'; 
	std::cout << " Service Name: " << m_name << '\n';
}


// ==== CMD HANDLING ====
std::string Service::Service0::getCommand()
{
    return m_name;
}


void Service::Service0::processTerminalCommadns(const std::vector<std::string>& vecOfCommandTokens) 
{
	checkChildCommands(vecOfCommandTokens);

	// After exit from method, reset layer counter
	layerDepth = 0;
}


void Service::Service0::checkChildCommands(const std::vector<std::string>& vecOfCommandTokens) 
{
    // STEP : 1 - This is last Node
    // Already processed - Go layer up
    if(m_vecChildCommands.size() == 0)
    {
        std::cout << "Last NODE: " << getCommand() << '\n';
        layerDepth--;
        return;
    }

    std::cout << "Parent NODE: " << getCommand() << " layerDepth: " << layerDepth << '\n';
       
    try {
        // Check if next terminal command exists
        std::cout << " Next terminal command: " << vecOfCommandTokens.at(layerDepth + 1) << " exists. Go deeper ... " << '\n';
        vecOfCommandTokens.at(layerDepth + 1);
    } catch (...) {
        // Next terminal command does not exists - go back
        layerDepth--;
        std::cout << " Next terminal command does not exist. Go back ... " << '\n';
        return;
    }

    // STEP : 2 - If this is not last Node and next terminal command exists
    // Process - Go layer down ...
    for(auto s : m_vecChildCommands)
    {
        std::cout << " Compare child node command: " << s->getCommand() << " to terminal command: "<< vecOfCommandTokens.at(layerDepth + 1) << '\n';
        if(!s->getCommand().compare(vecOfCommandTokens.at(layerDepth + 1)))
        {
            // Process command in current node ...
            // IMORTANT: We are still in parent node so s Node (Child) is layerDepth + 1
            s->cmdHandler(vecOfCommandTokens, layerDepth + 1);
            // ... go deeper
            layerDepth++;
            s->checkChildCommands(vecOfCommandTokens);
        }
    }

    // No more NODEs in vector of nodes
    std::cout << "Node: " << getCommand() << " - No more NODEs in vector of nodes" << '\n';
    layerDepth--;

    return;
}


void Service::Service0::cmdHandler(const std::vector<std::string>& vecOfStringTokens, int depth)
{
    std::cout << "----" << '\n';
    std::cout << "... Processing rest of commands in NODE ..." << m_name << '\n';
       
    for(int i = depth + 1; i < vecOfStringTokens.size(); i++)
    {
        std::cout << "  " << vecOfStringTokens.at(i) << '\n';
    }

    std::cout<< "Depth : " << depth << '\n';
    std::cout << "----" << '\n';
}


void Service::Service0::cmdPrompt(const std::string& arg0)
{
	int ONE = 1;
	int TWO = 2;
	int THREE = 3;
	// -- FIRST DEFINE arg0 --
	std::istringstream stringOfElements(arg0);
	std::vector<std::string> vectorOfLocalStrings((std::istream_iterator<std::string>(stringOfElements)), std::istream_iterator<std::string>());

	std::string regexPattern;
	if (vectorOfLocalStrings.size() == TWO)
	{
		regexPattern = "services\\s+" + m_name;
	}
	else if (vectorOfLocalStrings.size() == THREE)
	{
		regexPattern = "services\\s+" + m_name + "\\s+(\\w+)";
	}
	// ----

	std::smatch match;
	std::regex _regex(regexPattern);
	if (std::regex_search(arg0, match, _regex))
	{
		if (vectorOfLocalStrings.size() == TWO)
		{
			std::cout << " services " << m_name << " <set | dump>" << std::endl;
		}
		else if (vectorOfLocalStrings.size() == THREE)
		{
			if (!match.str(1).compare("dump"))
			{
				dump();
			}
		}		
	}
}