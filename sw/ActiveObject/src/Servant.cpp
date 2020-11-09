#include "Servant.h"
#include "Factory.h"


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
    FACTORY.getLog()->LOGFILE(LOG "Servant: " + m_name + " checkEmpty(). Check if avail to do operation on AO"); 
} 


bool ActiveObject::Servant::checkFull(void) const
{  
    FACTORY.getLog()->LOGFILE(LOG "Servant: " + m_name + " checkFull(). Check if avail to do operation on AO"); 
    return 0; 
}


// Message queue implementation operations.  
void ActiveObject::Servant::put(const Message& msg)  
{  
    // std::cout << " [Servant][put_i] Putting Message in AO: " << msg << std::endl; 
    FACTORY.getLog()->LOGFILE(LOG "Servant: " + m_name + " execute method put(const Message& msg)"); 
    m_messages.push_back(msg);  
}  