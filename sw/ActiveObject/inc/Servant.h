#include <string>
#include <vector>
#include <iostream>

// [3]  
namespace ActiveObject
{
class Servant  
{  
public:  
// Constructor  
    Servant(int id);
 
// Message queue implementation operations.  
/*    void put(const Message& msg)  
    {  
        std::cout << " [Servant][put_i] Putting Message in AO: " << msg << std::endl;  
        m_messages.push_back(msg);  
    }  
    
    Message get(void)  
    {  
        std::cout << " [Servant][get] Getting Message: - " << std::endl;  
    }*/

// Predicates.  
    bool checkEmpty(void) const;  

    bool checkFull(void) const;

private:  
int m_id;  
// std::vector<Message> m_messages;
};  
}