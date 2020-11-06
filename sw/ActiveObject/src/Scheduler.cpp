#include "Scheduler.h"
#include "Factory.h"


ActiveObject::Scheduler::Scheduler(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
/*	FACTORY.getLog()->LOGFILE(LOG "Control: " + m_name + " created.");
*/
	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';

	// FACTORY.getLog()->LOGFILE(LOG "Service: " + m_name + " created. [CONSTRUCTOR]");
}


void ActiveObject::Scheduler::preInit()  
{  
    std::cout << " [Scheduler][preInit] ..." << '\n';   
};  


void ActiveObject::Scheduler::postInit()  
{  
        std::cout << " [Scheduler][postInit] ..." << '\n';  
        // Get ActivationQueue instance from DB
        std::string dBKey = m_dbPathWithName + "activationQueue";
        std::cout << "dBKey actQueue: " << dBKey << '\n';

	    std::vector<std::string> activationQueue;
	    FACTORY.getDatabase()->getStringsFromDB(dBKey, activationQueue);    

        std::cout << "DB ActQueue: " << activationQueue[0] << '\n';
        auto actQueue = FACTORY.getActiveObjectIf(activationQueue[0]);  
        m_actQueueShared = actQueue;
        // m_actQueueShared->postInit();
};  


void ActiveObject::Scheduler::setActivationQueue(std::shared_ptr<ActiveObject::ActiveObjectIf>& act_queue)
{  
    std::cout << " [Scheduler][setActivationQueue] ..." << std::endl;  
    m_actQueueShared = act_queue;
     
}  


void ActiveObject::Scheduler::enqueue(MethodRequest* methodRequest)
{  
    std::cout << " [Scheduler][enqueue] Putting MR object in Activation Queue" << std::endl;  
    m_actQueueShared->enqueue(methodRequest);  
    this->dispatch();  
}  


void ActiveObject::Scheduler::dispatch()
{
        std::cout << " [Scheduler][dispatch] Calling ..." << std::endl;  

        std::vector<MethodRequest*>& mrVec = m_actQueueShared->getMrVec();  

        std::vector<MethodRequest*>::iterator it = mrVec.begin();  
        //std::cout << " ---- Before while. mrVec.size() = " << mrVec.size() << std::endl;  

        while (it != mrVec.end())  
        {  
            MethodRequest* mr = *it;  
            //std::cout << " ---- In while" << std::endl;  
            if ((*it)->guard())  
            {  
                // First do operation on servant (Active Object)  
                (*it)->call();  
                // delete from vector in real time  
                it = mrVec.erase(it);  
                delete mr;  
            }  
            else  
            {  
                it++;  
            }  
        }
}