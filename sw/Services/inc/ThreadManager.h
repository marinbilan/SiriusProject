#pragma once
#include "ServiceIf.h"
#include "ActiveObjectIf.h"
#include <future>


namespace Service
{

class ThreadManager : public ServiceIf
{
public:
	ThreadManager(const std::string& dbPath, const std::string& name);
	~ThreadManager();

	const std::string& getName()
	{
		return m_name;
	}

	void preInit();
	void postInit();

	void startAllThreads();

    // cmd handling
	void dump();
	void cmdPrompt(const std::string& arg0);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

// THREADING
std::future<void> fut;

std::shared_ptr<ActiveObject::ActiveObjectIf> m_schedulerShared;
};
}