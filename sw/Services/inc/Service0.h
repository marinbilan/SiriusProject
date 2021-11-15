#pragma once
#include "ServiceIf.h"
#include "CommonIf.h"


namespace Service
{
class Service0 : public ServiceIf, public Common::CommonIf
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

	void testMethod();

    // cmd handling
    std::string getCommand();
    void processTerminalCommadns(const std::vector<std::string>& vecOfCommandTokens);
    void checkChildCommands(const std::vector<std::string>& vecOfCommandTokens);
    void cmdHandler(const std::vector<std::string>& vecOfStringTokens, int depth);

	void dump();
	void cmdPrompt(const std::string& arg0);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

std::vector<std::shared_ptr<Common::CommonIf>> m_vecOfCommonIf;

// cmd handling
static int layerDepth;
// std::string m_command;

std::vector<std::shared_ptr<Common::CommonIf>> m_vecChildCommands;
bool visited;

};
}