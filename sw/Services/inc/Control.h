#pragma once
#include "ControlIf.h"


namespace Control
{

class Control : public ControlIf
{
public:
	Control(const std::string& dbPath, const std::string& name);
	~Control();

	const std::string& getName()
	{
		return m_name;
	}

	void preInitialization();
	void postInitialization();

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;
};
}