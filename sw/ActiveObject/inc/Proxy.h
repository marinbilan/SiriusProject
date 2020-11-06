#pragma once
#include "ActiveObjectIf.h"

#include "Servant.h"
#include "Scheduler.h"


namespace ActiveObject
{
class Proxy : public ActiveObjectIf
{  
public:
    Proxy(const std::string& dbPath, const std::string& name);

    const std::string& getName()
	{
		return m_name;
	}

    void preInit();
    void postInit();

    void put(const Message &msg);

    // Message_Future get(void);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;
 
std::shared_ptr<ActiveObject::ActiveObjectIf> m_schedulerShared;
std::shared_ptr<ActiveObject::ActiveObjectIf> m_servantShared; 
};  
}