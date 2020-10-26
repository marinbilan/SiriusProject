// #pragma once
#include "Service0.h"

#include "Factory.h"

#include <chrono>
#include <thread>

#include "EventHandlerIf.h"
#include "EventHandler.h"
#include "InitiationDispatcher.h"
#include "LoggingAcceptor.h"

Service::Service0::Service0(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
/*	FACTORY.getLog()->LOGFILE(LOG "Control: " + m_name + " created.");
*/
	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';

	FACTORY.getLog()->LOGFILE(LOG "Service: " + m_name + " created. [CONSTRUCTOR]");
}


Service::Service0::~Service0()
{
}


void Service::Service0::preInit()
{
	std::cout << "preInitialization - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


void Service::Service0::postInit()
{
	// std::cout << " xxx Service0_0 POSTINIT" << '\n';
	/*while(1) 
    {
        std::cout << " print from postInit ... " << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }*/

	// REACTOR
	// Reactor::Logging_Acceptor la(0);
    // Reactor::InitiationDispatcher::getInstance().init();
    // Reactor::InitiationDispatcher::getInstance().handle_events();
}


void Service::Service0::dump()
{
    std::cout << " Service DbPathWithName: " << m_dbPathWithName << '\n'; 
	std::cout << " Service Name: " << m_name << '\n';
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