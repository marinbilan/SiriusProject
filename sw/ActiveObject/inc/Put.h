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
    Put(ActiveObjectIf* rep, Message arg); 

    // First check is ActiveObject (servant) is ready from Scheduler
    virtual bool guard(void) const;
    
    // Second execute action on ActiveObject from Scheduler
    virtual void call(void);

private:  
ActiveObjectIf* m_servant;  
Message m_arg;
};  
}