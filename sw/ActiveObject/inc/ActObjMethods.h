#pragma once
#include "MethodRequest.h"
#include "ActiveObjectIf.h"
#include "Servant.h"

#include "CommonTypes.h"


namespace ActiveObject
{
class Put : public MethodRequest  
{  
public:  
    Put(std::shared_ptr<ActiveObject::ActiveObjectIf>& servant, Message arg);

    // First check is ActiveObject (servant) is ready from Scheduler
    virtual bool guard(void) const;
    
    // Second execute action on ActiveObject from Scheduler
    virtual void call(void);

private:  
Message m_arg;

ActiveObjectIf* m_servant;
std::shared_ptr<ActiveObject::ActiveObjectIf> m_servantShared;
};  
}