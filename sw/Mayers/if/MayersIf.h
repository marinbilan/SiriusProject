#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include <memory>


namespace Mayers
{
class MayersIf
{
public:
    virtual ~MayersIf() 
    {
        // std::cout << "[MayersIf][~MayersIf] Mayers interface destructora called!" << std::endl;
    }

    virtual int getId() const
    {
        return 0;
    }

    virtual void toString() const
    {
    }

    virtual void testItem10_0()
    {
    }

};
} // End of Namespace