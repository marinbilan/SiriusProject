#include "Servant.h"


ActiveObject::Servant::Servant(int id) : 
	m_id(id)
{
    std::cout << "[Servant][Servant] Creating Servant object." << std::endl;
}

bool ActiveObject::Servant::checkEmpty(void) const
{  
    std::cout << " [Servant][checkEmpty] Getting Message: - " << std::endl;  
} 

bool ActiveObject::Servant::checkFull(void) const
{  
    std::cout << " [Servant][checkFull] Getting Message: [ Not Full ] " << std::endl;  
    return 0; 
}