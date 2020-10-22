#include "CmdPrompt.h"
#include "Factory.h"


Common::CmdPrompt::CmdPrompt(const std::string& name) : m_name(name)
{
}


Common::CmdPrompt::~CmdPrompt()
{
}


void Common::CmdPrompt::preInit()
{
}


void Common::CmdPrompt::postInit()
{
	runCmdPrompt();
}


void Common::CmdPrompt::runCmdPrompt()
{
	std::string commandLineString;
	std::smatch match;

	do
	{
		std::cout << "$ ";
		// Waiting for command
		std::getline(std::cin, commandLineString);

		std::regex oneWordLine("(\\w+)");
		// One word match
		if (std::regex_search(commandLineString, match, oneWordLine))
		{
			if (!match.str(1).compare("controls"))
			{
				cmdControls(commandLineString);
			}
			if (!match.str(1).compare("help"))
			{
				cmdHelp();
			}
		}
	} while (commandLineString != "run");
}


void Common::CmdPrompt::cmdControls(const std::string& str)
{
	int ONE = 1;
	int TWO = 2;
	int THREE = 3;
	// ----
	std::istringstream stringOfElements(str);
	std::vector<std::string> vectorOfLocalStrings((std::istream_iterator<std::string>(stringOfElements)), std::istream_iterator<std::string>());

	std::string regexPattern;
	// Default (Start string)
	if (vectorOfLocalStrings.size() == ONE)
	{
		std::cout << " controls <contolName | all>" << std::endl;
	}
	if (vectorOfLocalStrings.size() == TWO)
	{
		regexPattern = "controls\\s+(\\w+)";
	}
	else if (vectorOfLocalStrings.size() == THREE)
	{
		regexPattern = "controls\\s+(\\w+)\\s+(\\w+)";
	}
	// ----

	std::smatch match;
	std::regex _regex(regexPattern);
	if (std::regex_search(str, match, _regex))
	{
		// One word in cmd line
		if (vectorOfLocalStrings.size() == ONE)
		{
		}
		// Two words in cmd line or Three words in cmd line (all or modelName)
		else if (vectorOfLocalStrings.size() == TWO |
			     vectorOfLocalStrings.size() == THREE)
		{
			if (!match.str(1).compare("all"))
			{
				for (auto s : Common::Factory::getInstance().getControlIfVec())
				{
				    std::cout << " - " << s->getName() << '\n';
				}
			}
			else // If second word is not "all" (it should be model name or something else (unknown))
			{
				for (auto s : Common::Factory::getInstance().getControlIfVec())
				{
					if (!match.str(1).compare(s->getName()))
					{
						s->cmdPrompt(str);
					}
				}
			}
		}
	}
}


void Common::CmdPrompt::cmdHelp()
{
	std::string helpStr(" [ HELP ] \n"
	" | controls  Info about controls (Keys) \n" 
	" | read      Read from File ");

	std::cout << helpStr << '\n';
}