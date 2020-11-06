#pragma once
#include "ActiveObjectIf.h"


// [1]
namespace ActiveObject
{
class ActivationQueue : public ActiveObjectIf
{  
public:
    ActivationQueue(const std::string& dbPath, const std::string& name);

    const std::string& getName()
	{
		return m_name;
	}

    void preInit();
    void postInit();

    void enqueue(MethodRequest* methodRequest);

    std::vector<MethodRequest*>& getMrVec();

    void dequeue(MethodRequest* method_request);

private:  
std::string m_name;
std::string m_dbPath;
std::string m_dbPathWithName;

std::vector<MethodRequest*> m_messagesVector;
};
}  