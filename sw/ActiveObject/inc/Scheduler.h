#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "ActivationQueue.h"


// [2]
namespace ActiveObject
{
class Scheduler  
{  
public:  
    // Constructor  
    Scheduler(ActivationQueue* act_queue);

/*
    void enqueue(MethodRequest* methodRequest)  
    {  
        std::cout << " [Scheduler][enqueue] Putting MR object in Activation Queue" << std::endl;  
        m_actQueue->enqueue(methodRequest);  
        this->dispatch();  
    }  
*/
    // >>>> RUN THIS IN SEPARATE THREAD <<<<  
    virtual void dispatch(void);

protected:  
ActivationQueue* m_actQueue;  
};  
}