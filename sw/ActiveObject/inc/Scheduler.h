#pragma once
#include "ActiveObjectIf.h"
#include "ActivationQueue.h"


// [2]
namespace ActiveObject
{
class Scheduler : public ActiveObjectIf
{  
public:
    Scheduler(const std::string& dbPath, const std::string& name);

    const std::string& getName()
	{
		return m_name;
	}

    void preInit();
    void postInit();
    
    void setActivationQueue(std::shared_ptr<ActiveObject::ActiveObjectIf>& act_queue);
    // Place mutex in this method
    void enqueue(MethodRequest* methodRequest);

    // >>>> RUN THIS IN SEPARATE THREAD <<<<  
    void dispatch(void);

private:
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

std::shared_ptr<ActiveObject::ActiveObjectIf> m_actQueueShared;
};  
}