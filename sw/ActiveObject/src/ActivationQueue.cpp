#include "ActivationQueue.h"
#include "Factory.h"


ActiveObject::ActivationQueue::ActivationQueue(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
/*	FACTORY.getLog()->LOGFILE(LOG "Control: " + m_name + " created.");
*/
	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';

	// FACTORY.getLog()->LOGFILE(LOG "Service: " + m_name + " created. [CONSTRUCTOR]");
}


void ActiveObject::ActivationQueue::preInit()  
{  
    std::cout << " [ActivationQueue][preInit] ..." << '\n';   
};  


void ActiveObject::ActivationQueue::postInit()  
{  
        std::cout << " [ActivationQueue][postInit] ..." << '\n';   
};  


void ActiveObject::ActivationQueue::enqueue(MethodRequest* methodRequest)  
{  
    // std::cout << " [ActivationQueue][enqueue] Push MR object in enqueue vector." << std::endl;  
    FACTORY.getLog()->LOGFILE(LOG "ActivationQueue: " + m_name + " enqueue(MethodRequest* methodRequest) Push MR object in enqueue vector."); 

    m_messagesVector.push_back(methodRequest);  
};  


std::vector<ActiveObject::MethodRequest*>& ActiveObject::ActivationQueue::getMrVec()  
{  
    return m_messagesVector;  
}


void ActiveObject::ActivationQueue::dequeue(MethodRequest* method_request)  
{  
    std::cout << " ActivationQueue dequeue. " << std::endl;  
} 