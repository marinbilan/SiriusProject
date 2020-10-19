#pragma once
#include <iostream>


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

private:
	std::string returnErrorStr = "Error: ControlIf::getName() called from ControlIf!";
};
}