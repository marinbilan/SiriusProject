#include "Servant.h"


ActiveObject::Servant::Servant(const std::string& dbPath, const std::string& name) : 
	m_dbPath(dbPath),
	m_name(name)
{
/*	FACTORY.getLog()->LOGFILE(LOG "Control: " + m_name + " created.");
*/
	m_dbPathWithName = m_dbPath + m_name + "_";
	std::cout << " CREATION INSTANCE - m_dbPathWithName: " << m_dbPathWithName << " modelName: " << m_name << '\n';

	// FACTORY.getLog()->LOGFILE(LOG "Service: " + m_name + " created. [CONSTRUCTOR]");
}


void ActiveObject::Servant::preInit()
{  
    std::cout << " [Servant][preInit] ... " << std::endl;  
} 


void ActiveObject::Servant::postInit()
{  
    std::cout << " [Servant][postInit] ... " << std::endl;  
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