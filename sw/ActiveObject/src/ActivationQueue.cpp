#include "ActivationQueue.h"


ActiveObject::ActivationQueue::ActivationQueue(const std::string& name) : 
	m_name(name) 
{
    std::cout << "[ActivationQueue][ActivationQueue] Creating ActivationQueue object." << '\n';
}


void ActiveObject::ActivationQueue::dummyMethod()
{
    std::cout << "[ActivationQueue][dummyMethod] ..." << '\n';
}