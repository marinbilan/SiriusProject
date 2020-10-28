#include "Scheduler.h"


ActiveObject::Scheduler::Scheduler(ActivationQueue* act_queue) : 
	m_actQueue(act_queue)
{
    std::cout << "[Scheduler][Scheduler] Creating Scheduler object." << std::endl;
}


void ActiveObject::Scheduler::dispatch()
{
        std::cout << " [Scheduler][dispatch] Calling ..." << std::endl;  
/*
        std::vector<MethodRequest*>& mrVec = m_actQueue->getMrVec();  

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
        */ 
}