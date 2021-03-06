#pragma once
#include <map>  
#include <string>  
#include <iostream>  
#include <memory>  
#include <vector>  
#include <functional>
#include <optional>

// Common
#include "Database.h"
#include "Log.h"

#include "ControlIf.h"
#include "Control.h"

// Services
#include "ServiceIf.h"
#include "Service0.h"
#include "ThreadManager.h"

// Active Object
#include "ActiveObjectIf.h"
#include "ActivationQueue.h"
#include "Scheduler.h"
#include "Servant.h"
#include "Proxy.h"

/*
*	[PREPARATION STEP : 2]
*		Object Registration
*		- Register class calling registerClass method (ClassName, constructorPtr(const str&, const str&))
*		- Register class in map with registerClass method
*/
#define REGISTER_CLASS(ConstructorName) Common::Factory::getInstance().registerClass<ConstructorName>(#ConstructorName)


namespace Common
{
	/*! @brief 
	*	[CREATION STEP : 2] Method for object construction
	*		- Construct instance out of template constructor
	*
	*	@param arg0 instanceDbPath (without instance name)
	*	@param arg1 instanceName
	*
	*   @return void ponter of created object
	*/
template <class T> void* constructorNew(const std::string& arg0, const std::string& arg1)
{
	return (void*)new T(arg0, arg1);
}

class Factory
{
public:
	/*! @brief  Get singleton factory instance
	*   @return Factory reference 
	*/
	static Factory& getInstance()
	{
		// std::cout << "This is constructor!" << '\n';
		static Factory instance;
		return instance;
	}

	~Factory() 
	{
		std::cout << "Factory destructor called!" << '\n';
	};

	Factory(Factory const&) = delete;
	void operator=(Factory const&) = delete;

	// ==== PREPARATION PHASE START ====
	/*! @brief  
	*	[PREPARATION STEP : 1] Register class using MACRO - Generator of objects	
	*		- Class registration (register constructor name calling MACRO)
	*
    *	@return void
	*/
	void registerClass()
	{
		// Services
		REGISTER_CLASS(Control::Control);
		REGISTER_CLASS(Service::Service0);
		REGISTER_CLASS(Service::ThreadManager);
		// Active Object
		REGISTER_CLASS(ActiveObject::ActivationQueue);
		REGISTER_CLASS(ActiveObject::Scheduler);
		REGISTER_CLASS(ActiveObject::Servant);
		REGISTER_CLASS(ActiveObject::Proxy);
	}

	//	[PREPARATION STEP : 2] - Object registration (See MACRO above)

	/*! @brief
	*	[PREPARATION STEP : 3] Last preparation step (after this step see constructObject method)
	*		Method for class registration - map(constructor name, constructor (template function) pointer)
	*		For now, construction pointer is template - will be filled when constructObject method is invoked
	*
	*	@param	constructor name - to create pair
	*
	*   @return void
	*/
	template <class T>
	void registerClass(std::string const& constructorName)
	{
		// First argument is constructor name
		// Second argument is classConstructorPointer (&constructorNew<T>) it is generic pointer to generic class constructor
		// Store this pair into m_classesMap
		m_classesMap.insert(std::make_pair(constructorName, &constructorNew<T>));
	}
	// ==== PREPARATION PHASE END ====


	// ==== CREATION PHASE START ====
	/*! @brief 
	*	[CREATION STEP : 1] Object creation step
	*	
	*   @param Namespace::constructorName - to find pair in m_classesMap
	*   @param arg0 instanceDbPath        - this is first argument in object constructor
	*							          - for getting stuff from db, related to instance
	*	@param arg1 instance name
	*
	*   @return void ponter of created object
	*/
	void* constructObject(std::string const& constructorName, const std::string& arg0, const std::string& arg1)
	{
		mapTypeNew::iterator i = m_classesMap.find(constructorName);

		if (i == m_classesMap.end()) return 0; // or throw or whatever you want  

		return i->second(arg0, arg1);
	}


	void preInit()
	{
        std::cout << "Factory preinit method called!" << '\n';

		// 1] DATABASE - Create DB and store it in Factory
		std::unique_ptr<Common::Database> database = std::make_unique<Common::Database>("../sw/_DB/database_0.txt");
		Common::Factory::getInstance().setDatabase(database);

		// Create global Error object
		// m_error = std::make_unique<Common::Error>();

		// 2] Create global Log object
		m_log = std::make_unique<Common::Log>("log_0");

		// 3] Register all classes using REGISTER_CLASS macro
		registerClass();
	}

	void postInit()
	{
		// Services
		for(auto s : m_vecOfServiceIf)
		{
			s->postInit();
		}
		
		// Active Object
		for(auto s : m_vecOfActiveObjectIf)
		{
			s->postInit();
		}
	}

	/*! @brief  Set database object created from init object (during init phase)
	*   @param  database
	*   @return void
	*/
	void setDatabase(std::unique_ptr<Common::Database>& database)
	{
		m_database = std::move(database);
	}


	/*! @brief  Get reference on global database object
     *  @return reference on database object
     */
	std::unique_ptr<Common::Database>& getDatabase()
	{
		return m_database;
	}


	/*! @brief  Get reference on global error object
	 *  @return reference on error object
	 */
	/*std::unique_ptr<Common::Error>& getErrorObject()
	{
		return m_error;
	}*/


	/*! @brief  Get reference on global log object
	 *  @param  -
	 *  @return reference on log object
	 */
	std::unique_ptr<Common::Log>& getLog()
	{
		return m_log;
	}


	/*! @brief  Create objects from DB
	[CREATION STEP : 1]
	 *  @return void
	 */
	void createObjects()
	{
		getLog()->LOGFILE(LOG "[FACTORY] CREATING OBJECTs");
		createAllObjects();

		// std::cout << '\n';
	}


	void createAllObjects()
	{
		std::string interfaces("Interfaces");
		std::vector<std::string> vecOfInterfacesStrings;

        // INTERFACEs
		// [0th DB Stage]: Interfaces    string  ServiceIf ...
        m_database->getStringsFromDB(interfaces, vecOfInterfacesStrings);

		for (auto s : vecOfInterfacesStrings)
		{
			createModels(s);
		}
	}

	/*
	Interfaces <- STARTing tags
		ServiceIf    (vecOfInterfacesStrings)
			Service0    (vecOfConstructorsStrings)
							(vecOfInstanceString)
				service0_0
				service1_0
				...
	*/

	void createModels(const std::string& interface)
	{
	    getLog()->LOGFILE(LOG "[FACTORY] Interface : " + interface);

		std::string interfacePath = interface;    // ServiceIf ...
		std::vector<std::string> vecOfConstructorsStrings;

        // DERIVED CLASSEs
		// [1th DB Stage]: ServiceIf    string      Service0, Service1 ...
        m_database->getStringsFromDB(interfacePath, vecOfConstructorsStrings);

		for (auto s : vecOfConstructorsStrings)
		{
			getLog()->LOGFILE(LOG "[FACTORY] Constructor : " + s);

			// For Constructor (1st argument): "ServiceIf_Service0_" - Just DB path for each instance
			std::string instanceDbPath = interfacePath + "_" + s + "_"; // arg0 of constructor - Instance dB locator

			std::string constructorNameDbPath = interfacePath + "_" + s + "_" + "constructorName";
			std::vector<std::string> vecOfConstructorString;
			// For Constructor pointers map (2nd arg) - vecOfConstructorString[0]: "Service::Service0"
            m_database->getStringsFromDB(constructorNameDbPath, vecOfConstructorString);

			std::string instanceNameDbPath = interfacePath + "_" + s + "_" + "instanceNames";
			std::vector<std::string> vecOfInstanceString;
			// ex vecOfInstanceString: "service0_0"
            m_database->getStringsFromDB(instanceNameDbPath, vecOfInstanceString);

			// Create each instance and store in container with pointer on instance interface
			// ex: service0_0, service0_1 ...
			for (auto s : vecOfInstanceString)
			{
				// STEP: 2 - If new interface needs to be added, add it here
				if (!interfacePath.compare("controls"))
				{
					std::shared_ptr<Control::ControlIf> controlInstance((Control::ControlIf*)constructObject(vecOfConstructorString[0], instanceDbPath, s));
					controlInstance->preInit();

					storeInContainer("ControlIf", controlInstance); 
					std::cout << ".";
				}
				if (!interfacePath.compare("ServiceIf"))
				{
					getLog()->LOGFILE(LOG "[FACTORY] Creating Instance : " + s);

					std::shared_ptr<Service::ServiceIf> serviceInstance((Service::ServiceIf*)constructObject(vecOfConstructorString[0], instanceDbPath, s));
					serviceInstance->preInit();

					storeInContainer("ServiceIf", serviceInstance); 
					std::cout << ".";
				}
				if (!interfacePath.compare("ActiveObjectIf"))
				{				
					std::shared_ptr<ActiveObject::ActiveObjectIf> activeObjectInstance((ActiveObject::ActiveObjectIf*)constructObject(vecOfConstructorString[0], instanceDbPath, s));
					activeObjectInstance->preInit();					

					storeInContainer("ActiveObjectIf", activeObjectInstance); 
					std::cout << ".";
				}
				else 
				{					
				}
			}
		}
	}


	// TODO: Remove Template setter (store)
	/*	void storeInContainer(const std::shared_ptr<GPUObject::MeshStructure>& meshStruct)
	{
		m_vecOfMeshStructure.push_back(meshStruct);
	}

	void storeInContainer(const std::shared_ptr<GPUObject::RawTextureStructure>& rawTextureStruct)
	{
		m_vecOfRawTextureStructure.push_back(rawTextureStruct);
	}*/


	/*! @brief Store object in container
	 *  @param - objNameIf
	 *  @param - derivedObject
	 *  @return void
	 */
	template<class T>
	void storeInContainer(const std::string& objNameIf, const T& derivedObject)
	{
		// STEP: 3
		if (!objNameIf.compare("ControlIf"))
		{
			m_vecOfControlIf.push_back(std::dynamic_pointer_cast<Control::ControlIf>(derivedObject));
		}
		if (!objNameIf.compare("ServiceIf"))
		{
			m_vecOfServiceIf.push_back(std::dynamic_pointer_cast<Service::ServiceIf>(derivedObject));
		}
		if (!objNameIf.compare("ActiveObjectIf"))
		{
			m_vecOfActiveObjectIf.push_back(std::dynamic_pointer_cast<ActiveObject::ActiveObjectIf>(derivedObject));
		}
		else
		{
			// FACTORY.getErrorObject()->setError("ERROR: " + objNameIf + " can not be found!");
			// FACTORY.getLog()->LOGFILE(LOG "ERROR: " + objNameIf + " can not be found!");
		}
	}


	/*! @brief Show classes registered in map m_classesMap(constructorName, construcor pointer)
	 *  @return void
	 */
	void showMeSeededClasses()
	{
		mapTypeNew::iterator it;
		for (it = m_classesMap.begin(); it != m_classesMap.end(); ++it)
		{
			std::cout << " - " << it->first << "\n";
		}
	}


	/*! @brief Show all objects generated from classes within one interface
	 *  @return void
	 */
	void showMeObjects(const std::string& objNameIf)
	{
		if (!objNameIf.compare("ControlIf"))
		{
			// printName(m_vecOfControlIf);
		}
		else
		{
			// Print something ... msg
		}
	}
	
	template<class T>
	void printName(T& vec0)
	{
		for (auto it = vec0.begin(); it != vec0.end(); ++it)
		{
			std::cout << (*it)->getName() << '\n';
		}
	}


	// GET object - TODO: Make this generic
	/*! @brief get object (within particaulary interface) from container
	 *  @param - objNameIf
	 *  @param - derivedObject
	 *  @return void
	 */
	// STEP: 4
	// -- Get vector of instances via Interface --
	std::vector<std::shared_ptr<Control::ControlIf>>& getControlIfVec()
	{
		return m_vecOfControlIf;
	}

	std::vector<std::shared_ptr<Service::ServiceIf>>& getServiceIfVec()
	{
		return m_vecOfServiceIf;
	}

	std::vector<std::shared_ptr<ActiveObject::ActiveObjectIf>>& getActiveObjectIfVec()
	{
		return m_vecOfActiveObjectIf;
	}

	// STEP: 5
	// -- Get instance via Interface --
	std::shared_ptr<Control::ControlIf>& getControlIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfControlIf, arg0);
	}


	std::optional<std::shared_ptr<Service::ServiceIf>> getServiceIf(const std::string& arg0)
	{
		getLog()->LOGFILE(LOG "Try to get ServiceIf instance: " + arg0);

		for (auto it = m_vecOfServiceIf.begin(); it != m_vecOfServiceIf.end(); ++it)
		{
			if (!(*it)->getName().compare(arg0))
			{
				return *it;
			}
		}

		getLog()->LOGFILE(LOG "No instance: " + arg0 + " in m_vecOfServiceIf. Return optional");

		return {};
	}


	std::shared_ptr<ActiveObject::ActiveObjectIf>& getActiveObjectIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfActiveObjectIf, arg0);
	}
	// ----

	// Generic getter 
	template<class T>
	auto getObjectFromVec(T& vec0, const std::string& arg1) -> decltype(vec0.at(0))
	{
		for (auto it = vec0.begin(); it != vec0.end(); ++it)
		{
			if (!(*it)->getName().compare(arg1))
			{
				return *it;
			}
		}

		// If not found, return nullptr
		// std::cout << " NOT FOUND: " << arg1 << " Returning: " << vec0[0]->getName() << '\n';
	
		return vec0[0];
	}


private:	
	// Singleton Factory - Private Constructor
	Factory() 
	{
	};

	// Factory Stuff 
	// - Create map(ConstructorName, constructorPtr) constructorPtr(str, str)
	typedef void* (*constructor_NEW)(const std::string&, const std::string&);
	typedef std::map<std::string, constructor_NEW> mapTypeNew;
	mapTypeNew m_classesMap;

	// DataBase
	std::unique_ptr<Common::Database> m_database;
	// Error
	// std::unique_ptr<Common::Error> m_error;
	// Log
	std::unique_ptr<Common::Log> m_log;


	// Container Stuff
	// STEP: 6
	std::vector<std::shared_ptr<Control::ControlIf>> m_vecOfControlIf;
	std::vector<std::shared_ptr<Service::ServiceIf>> m_vecOfServiceIf;
	std::vector<std::shared_ptr<ActiveObject::ActiveObjectIf>> m_vecOfActiveObjectIf;
};
} // End of namespace