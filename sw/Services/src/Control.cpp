// #pragma once
#include "Control.h"

#include "Factory.h"


Control::Control::Control(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
/*	FACTORY.getLog()->LOGFILE(LOG "Control: " + m_name + " created.");
*/
	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';

	FACTORY.getLog()->LOGFILE(LOG "Control: " + m_name + " created. [CONSTRUCTOR]");
}


Control::Control::~Control()
{
}


void Control::Control::preInitialization()
{
	std::cout << "preInitialization - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';
}


void Control::Control::postInitialization()
{

}


void Control::Control::dump()
{
    std::cout << " Control DbPathWithName: " << m_dbPathWithName << '\n'; 
	std::cout << " Control Name: " << m_name << '\n';
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