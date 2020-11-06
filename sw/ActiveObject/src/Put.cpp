#include "Put.h"


ActiveObject::Put::Put(ActiveObjectIf* rep, Message arg) 
    : m_servant(rep), m_arg(arg)  
{  
    std::cout << "[MethodRequest][Put] Creating Put MR object." << std::endl;  
} 


bool ActiveObject::Put::guard(void) const  
{  
    return !m_servant->checkFull();  
}  


void ActiveObject::Put::call(void)
{  
    m_servant->put(m_arg);
} 