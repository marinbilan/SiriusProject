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

    // cmd handling
	void dump();
	void cmdPrompt(const std::string& arg0);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;
};
}