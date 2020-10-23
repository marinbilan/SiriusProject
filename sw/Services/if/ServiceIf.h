#pragma once
#include <iostream>
#include "CommonTypes.h"
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

	virtual void preInitialization() {};
	virtual void postInitialization() {};

    // cmd handling
	virtual void dump() {};
	virtual void cmdPrompt(const std::string& arg0)
	{
	}

private:
	std::string returnErrorStr = "Error: ServiceIf::getName() called from ServiceIf!";
};
}