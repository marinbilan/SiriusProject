#pragma once
#include "ServiceIf.h"


namespace Service
{

class Service0 : public ServiceIf
{
public:
	Service0(const std::string& dbPath, const std::string& name);
	~Service0();

	const std::string& getName()
	{
		return m_name;
	}

	void preInit();
	void postInit();

    // cmd handling
	void dump();
	void cmdPrompt(const std::string& arg0);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;
};
}