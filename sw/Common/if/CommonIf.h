#pragma once
#include <string>
#include <iostream>
#include <vector>


namespace Common
{
class CommonIf
{
public:
	virtual ~CommonIf()
	{
		// std::cout << "Error: CommonIf::~CommonIf() called from CommonIf!" << '\n';
	}

	virtual void testMethod() 
	{}

	// Cmd Handling
	virtual std::string getCommand()
	{}

	virtual void processTerminalCommadns(const std::vector<std::string>& vecOfCommandTokens)
    {}

	virtual void checkChildCommands(const std::vector<std::string>& vecOfCommandTokens)
    {}

    virtual void cmdHandler(const std::vector<std::string>& vecOfStringTokens, int depth)
    {}
};

}