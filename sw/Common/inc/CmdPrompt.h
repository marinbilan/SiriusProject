#pragma once

#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include <iterator>


namespace Common
{
class CmdPrompt
{
public:
	CmdPrompt(const std::string& name);
	~CmdPrompt();

	void preInit();
	void postInit();

	void runCmdPrompt();

	// cmd handling
	void cmdControls(const std::string& str);
	void cmdHelp();

private:
std::string m_name;
};
}