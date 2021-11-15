#pragma once
#include <iostream>
#include <memory.h>
#include "CommonTypes.h"
#include "Database.h"
#include "Log.h"

namespace Service
{
class ServiceIf
{
public:
	~ServiceIf()
	{
	}

	virtual const std::string& getName()
	{
		return returnErrorStr;
	}

	virtual void preInit() {};
	virtual void postInit() {};

	// Thread Manager
	virtual void startAllThreads() {};

    // cmd handling
	virtual void dump() {};
	virtual void cmdPrompt(const std::string& arg0)
	{
	}

private:
	std::string returnErrorStr = "Error: ServiceIf::getName() called from ServiceIf!";
};
}