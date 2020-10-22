#pragma once
#include <iostream>
#include "CommonTypes.h"
#include "Log.h"

namespace Control
{
class ControlIf
{
public:
	~ControlIf()
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
	std::string returnErrorStr = "Error: ControlIf::getName() called from ControlIf!";
};
}