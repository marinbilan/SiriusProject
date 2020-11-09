#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "ActiveObjectIf.h"

// [3]  
namespace ActiveObject
{
class Servant : public ActiveObjectIf
{  
public:
    Servant(const std::string& dbPath, const std::string& name);

    const std::string& getName()
	{
		return m_name;
	}
    
    // Common
    void preInit();
    void postInit();

    // Message queue implementation operations.  
    void put(const Message& msg);

    /*    
    Message get(void)  
    {  
        std::cout << " [Servant][get] Getting Message: - " << std::endl;  
    }*/

    // Predicates.  
    bool checkEmpty(void) const;  

    bool checkFull(void) const;

private:  
std::string m_dbPath;
std::string m_dbPathWithName;
std::string m_name;

int m_id;  
std::vector<Message> m_messages;
};  
}