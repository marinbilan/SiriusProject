// #pragma once
#include "ThreadManager.h"

#include "Factory.h"

#include <chrono>
#include <thread>

#include "Factory.h"

Service::ThreadManager::ThreadManager(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
	m_dbPathWithName = m_dbPath + m_name + "_";
	FACTORY.getLog()->LOGFILE(LOG "ThreadManager: " + m_name + " created. [CONSTRUCTOR]"); 
}


Service::ThreadManager::~ThreadManager()
{
}


void Service::ThreadManager::preInit()
{
    std::cout << " [ThreadManager][preInit] ..." << '\n';  
}


void Service::ThreadManager::postInit()
{
    FACTORY.getLog()->LOGFILE(LOG "ThreadManager: " + m_name + " postInit().");
	std::cout << " [ThreadManager][postInit] ..." << '\n'; 

    // Get scheduler instance name from database
	std::vector<std::string> scheduler;
    std::string dBKey = m_dbPathWithName + "scheduler";
    // TODO: Print error if no instance from db
	FACTORY.getDatabase()->getStringsFromDB(dBKey, scheduler);    
	std::cout << "m_dbPathWithName:" << m_dbPathWithName << " scheduler:" << scheduler[0] <<'\n';
    // Get scheduler instance from factory container via instance name
    // TODO: Print error if no instance from factory
    auto schedulerInst = FACTORY.getActiveObjectIf(scheduler[0]);
    // Set scheduler
    m_schedulerShared = schedulerInst;


	// START ALL THREADs
	// startAllThreads();
}


void Service::ThreadManager::startAllThreads()
{
    std::cout << " ThreadManager **** START ALL THREADS **** " << m_schedulerShared->getName() << '\n';
	fut = std::async(&ActiveObject::ActiveObjectIf::dispatch, m_schedulerShared);
}


void Service::ThreadManager::dump()
{
    std::cout << " Service DbPathWithName: " << m_dbPathWithName << '\n'; 
	std::cout << " Service Name: " << m_name << '\n';
}


void Service::ThreadManager::cmdPrompt(const std::string& arg0)
{
	/*
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
	*/
}