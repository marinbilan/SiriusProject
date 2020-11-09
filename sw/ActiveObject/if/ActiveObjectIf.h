#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "CommonTypes.h"
#include "MethodRequest.h"


namespace ActiveObject
{
class ActiveObjectIf  
{  
public: 
	~ActiveObjectIf()
	{
	}

	virtual const std::string& getName()
	{
		return returnErrorStr;
	}

    // Common
    virtual void preInit() {};
    virtual void postInit() {};

    // [1] ActivationQueue
    virtual void enqueue(MethodRequest* methodRequest) {};

    virtual std::vector<MethodRequest*>& getMrVec()  {};

    virtual void dequeue(MethodRequest* method_request) {}; 

    // [2] Scheduler
    virtual void setActivationQueue(std::shared_ptr<ActiveObject::ActiveObjectIf>& act_queue) {};

    // >>>> RUN THIS IN SEPARATE THREAD <<<<  
    virtual void dispatch(void) {};

    // [3] Servant
    virtual bool checkEmpty(void) const {}; 
 
    virtual void put(const Message& msg) {};

    virtual Message get(void) {};

    virtual bool checkFull(void) const {};

    // [4] Proxy

private:
    std::string returnErrorStr = "Error: ActiveObjectIf::getName() called from ActiveObjectIf!";
};
}