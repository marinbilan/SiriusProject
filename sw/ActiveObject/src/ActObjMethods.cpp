#include "ActObjMethods.h"


ActiveObject::Put::Put(std::shared_ptr<ActiveObject::ActiveObjectIf>& servant, Message arg) 
    : m_servantShared(servant), m_arg(arg)  
{  
    std::cout << "[MethodRequest][Put] Creating Put MR object." << std::endl;  
} 


bool ActiveObject::Put::guard(void) const  
{  
    // return !m_servant->checkFull();  
    return !m_servantShared->checkFull();
}  


void ActiveObject::Put::call(void)
{  
    // m_servant->put(m_arg);
    m_servantShared->put(m_arg);
} 