#include "Proxy.h"
#include "ActObjMethods.h"
#include "Factory.h"


ActiveObject::Proxy::Proxy(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
	FACTORY.getLog()->LOGFILE(LOG "Proxy: " + m_name + " created.");

	m_dbPathWithName = m_dbPath + m_name + "_";
}


void ActiveObject::Proxy::preInit()  
{  
    FACTORY.getLog()->LOGFILE(LOG "Proxy: " + m_name + " preInit().");
};  


void ActiveObject::Proxy::postInit()  
{  
    FACTORY.getLog()->LOGFILE(LOG "Proxy: " + m_name + " postInit().");
    // Get scheduler instance name from database
	std::vector<std::string> scheduler;
    std::string dBKey = m_dbPathWithName + "scheduler";
    // TODO: Print error if no instance from db
	FACTORY.getDatabase()->getStringsFromDB(dBKey, scheduler);    
    // Get scheduler instance from factory container via instance name
    // TODO: Print error if no instance from factory
    auto schedulerInst = FACTORY.getActiveObjectIf(scheduler[0]);
    // Set scheduler
    m_schedulerShared = schedulerInst;
    

    // Get servant instance name from database
	std::vector<std::string> servant;
    dBKey = m_dbPathWithName + "servant";
	FACTORY.getDatabase()->getStringsFromDB(dBKey, servant);    
    // Get servant instance from factory container via instance name
    auto servantInst = FACTORY.getActiveObjectIf(servant[0]);
    // Set servant
    m_servantShared = servantInst;
};  


void ActiveObject::Proxy::put(const Message& msg)  
{  
    FACTORY.getLog()->LOGFILE(LOG "Proxy: " + m_name + " put(const Message& msg) Creating MR Put object.");

    ActiveObject::MethodRequest* methodRequest = new ActiveObject::Put(m_servantShared, msg);  
    m_schedulerShared->enqueue(methodRequest);
}


/*
Message_Future ActiveObject::Proxy::get(void)  
{  
    Message_Future result;  
    Method_Request *method_request = new Get(servant, result);  
    scheduler_->enqueue (method_request);  
    return result;  
}*/