// #pragma once
#include "Control.h"

#include "Factory.h"
#include "CmdPrompt.h"

#include <future>


Control::Control::Control(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
	m_dbPathWithName = m_dbPath + m_name + "_";
	FACTORY.getLog()->LOGFILE(LOG "[CONSTRUCTOR]: " + m_name + " created.");
}


Control::Control::~Control()
{
}


void Control::Control::preInit()
{
	FACTORY.getLog()->LOGFILE(LOG "[PREINIT]: " + m_name);
}


void Control::Control::postInit()
{
	FACTORY.getLog()->LOGFILE(LOG "[POSTINIT]: " + m_name);

	// ---- MAIN START ----
	// REACTOR
	std::shared_ptr<Service::ServiceIf> srvInst = FACTORY.getServiceIf("service0_0");
	// auto fut = std::async(&Service::ServiceIf::postInit, srvInst);
	srvInst->postInit();

    // CMD PROMPT
    Common::CmdPrompt cmd("TestCmd");
    cmd.runCmdPrompt();
}


void Control::Control::dump()
{

	std::cout << " Control Name: " << m_name << '\n';
    std::cout << " Control DbPathWithName: " << m_dbPathWithName << '\n'; 
}


void Control::Control::cmdPrompt(const std::string& arg0)
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
		regexPattern = "controls\\s+" + m_name;
	}
	else if (vectorOfLocalStrings.size() == THREE)
	{
		regexPattern = "controls\\s+" + m_name + "\\s+(\\w+)";
	}
	// ----

	std::smatch match;
	std::regex _regex(regexPattern);
	if (std::regex_search(arg0, match, _regex))
	{
		if (vectorOfLocalStrings.size() == TWO)
		{
			std::cout << " controls " << m_name << " <set | dump>" << std::endl;
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