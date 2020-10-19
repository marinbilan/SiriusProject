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