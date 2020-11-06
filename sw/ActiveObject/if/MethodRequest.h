#pragma once


namespace ActiveObject
{
class MethodRequest  
{  
public:  
    virtual bool guard(void) const = 0;  
    virtual void call(void) = 0;  
};
}  