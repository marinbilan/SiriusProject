#include <string>
#include <vector>
#include <iostream>


// [1]
namespace ActiveObject
{
class ActivationQueue  
{  
public:  
    ActivationQueue(const std::string& name);
    
    void dummyMethod();
/*
    void enqueue(MethodRequest* methodRequest)  
    {  
        std::cout << " [ActivationQueue][enqueue] Push MR object in enqueue vector." << std::endl;  
        m_messagesVector.push_back(methodRequest);  
    };  

    std::vector<MethodRequest*>& getMrVec()  
    {  
        return m_messagesVector;  
    }  

    void dequeue(MethodRequest* method_request)  
    {  
        // std::cout << " ActivationQueue dequeue. " << std::endl;  
    }  
*/

private:  
std::string m_name;  
// std::vector<MethodRequest*> m_messagesVector;
};
}  