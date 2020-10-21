#pragma once
#include <map>  
#include <string>  
#include <iostream>  
#include <memory>  
#include <vector>  

#include "Database.h"
#include "ControlIf.h"
#include "Control.h"

// Map in class members (ClassName, constructorPtr(const str&, const str&))
// Register class in map with registerClass method
#define REGISTER_CLASS(ConstructorName) Common::Factory::getInstance().registerClass<ConstructorName>(#ConstructorName)

/*
Factory:
[1st STEP]
Class Registration
- Class registration (insert constructor pointer in map)

[2nd STEP]
Object Creation
- Create object out of map (find in map and create instance)
*/

namespace Common
{
/*! @brief  Method for object construction
*   @param  objectName Name (ID) of particaular instance
*   @return void pointer on particular created object
*/
// Constructor type (const str&, const str&)
// arg0 - instanceDbPath (without instance name)
// arg1 - instanceName
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
		static Factory instance;
		return instance;
	}

	~Factory() {};

	Factory(Factory const&) = delete;
	void operator=(Factory const&) = delete;

	/*! @brief Method for class registration - map(constructor name, constructor (function) pointer)
	*   @param constructorName Namespace::constructorName
	*   @return void
	*/
	// - ConstructorName (ex: Model::StaticModel) 
	template <class T>
	void registerClass(std::string const& constructorName)
	{
		m_classesMap.insert(std::make_pair(constructorName, &constructorNew<T>));
	}
	/*! @brief Method for object creation
	*   @param constructorName Namespace::constructorName
	*   @param arg0 object name
	*   @return void
	*/
	// - Find constructor pointer with constructorName and create object using that constructor pointer
	void* constructObject(std::string const& constructorName, const std::string& arg0, const std::string& arg1)
	{
		mapTypeNew::iterator i = m_classesMap.find(constructorName);
		if (i == m_classesMap.end()) return 0; // or throw or whatever you want  
		return i->second(arg0, arg1);
	}

	void preInit()
	{
        std::cout << "Factory preinit method called!" << '\n';
		// Create global Error object
		// m_error = std::make_unique<Common::Error>();
		// Create global Log object
		// m_log = std::make_unique<Common::Log>("log_0");

		registerClass();
	}


	void postInit()
	{
	}


	/*! @brief Set database object created from init object (during init phase)
	*   @param database
	*   @return void
	*/
	void setDatabase(std::unique_ptr<Common::Database>& database)
	{
		m_database = std::move(database);
	}


	/*! @brief Get reference on global database object
     *  @return reference on database object
     */
	std::unique_ptr<Common::Database>& getDatabase()
	{
		return m_database;
	}


	/*! @brief Get reference on global error object
	 *  @return reference on error object
	 */
	/*std::unique_ptr<Common::Error>& getErrorObject()
	{
		return m_error;
	}*/


	/*! @brief Get reference on global log object
	 *  @param -
	 *  @return reference on log object
	 */
	/*std::unique_ptr<Common::Log>& getLog()
	{
		return m_log;
	}*/


	/*! @brief Register class using MACRO - Generator of objects
     *  @return void
     */
	void registerClass()
	{
		// ControlIf
		REGISTER_CLASS(Control::Control);
	}


	/*! @brief Create objects from DB
	 *  @return void
	 */
	void createObjects()
	{
		std::cout << " [CREATING OBJECTs] ";
		createAllClusters();

		std::cout << '\n';
	}


	void createAllClusters()
	{
		std::string clusters("clusters");
		std::vector<std::string> vecOfClustersStrings;

		// DB: clusters    string    controls...
        m_database->getStringsFromDB(clusters, vecOfClustersStrings);

		for (auto s : vecOfClustersStrings)
		{
            std::cout << "xxx clusters: " << s << '\n';
			createModels(s);
		}
	}

	void createModels(const std::string& cluster)
	{   
		std::string dbPath1 = cluster;
		std::vector<std::string> vecOfModelsStrings;

		// DB ex: models    string    staticModel terrainModel ...
        m_database->getStringsFromDB(dbPath1, vecOfModelsStrings);

		for (auto s : vecOfModelsStrings)
		{
			// dB ex: instanceDbPath: "models_staticModel_"
			std::string instanceDbPath = dbPath1 + "_" + s + "_"; // arg0 of constructor - Instance dB locator

			std::string constructorNameDbPath = dbPath1 + "_" + s + "_" + "constructorName";
			std::vector<std::string> vecOfConstructorString;
			// ex vecOfConstructorString[0]: "Model::StaticModel"
            m_database->getStringsFromDB(constructorNameDbPath, vecOfConstructorString);

			std::string instanceNameDbPath = dbPath1 + "_" + s + "_" + "instanceNames";
			std::vector<std::string> vecOfInstanceString;
			// ex vecOfInstanceString: "vanquish"
            m_database->getStringsFromDB(instanceNameDbPath, vecOfInstanceString);

			// Create each instance
			// ex: vanquish ...
			for (auto s : vecOfInstanceString)
			{
				if (!dbPath1.compare("controls"))
				{
					std::shared_ptr<Control::ControlIf> controlInstance((Control::ControlIf*)constructObject(vecOfConstructorString[0], instanceDbPath, s));
					controlInstance->preInitialization();

					storeInContainer("ControlIf", controlInstance); 
					std::cout << ".";
				}
				else 
				{					
				}
			}
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
		if (!objNameIf.compare("ControlIf"))
		{
			m_vecOfControlIf.push_back(std::dynamic_pointer_cast<Control::ControlIf>(derivedObject));
		}
		else
		{
			// FACTORY.getErrorObject()->setError("ERROR: " + objNameIf + " can not be found!");
			// FACTORY.getLog()->LOGFILE(LOG "ERROR: " + objNameIf + " can not be found!");
		}
	}

	// GET object - TODO: Make this generic
	/*! @brief get object (within particaulary interface) from container
	 *  @param - objNameIf
	 *  @param - derivedObject
	 *  @return void
	 */
	// -- Get Controls via Interface --
	std::vector<std::shared_ptr<Control::ControlIf>>& getControlIfVec()
	{
		return m_vecOfControlIf;
	}
	/*std::shared_ptr<Control::ControlIf>& getControlIf(const std::string& arg0)
	{
		return getObjectFromVec(m_vecOfControlIf, arg0);
	}*/
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

		// If not found, return something
		std::cout << " NOT FOUND: " << arg1 << " Returning: " << vec0[0]->getName() << '\n';
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
	// std::unique_ptr<Common::Log> m_log;


	// Container Stuff
	std::vector<std::shared_ptr<Control::ControlIf>>     m_vecOfControlIf;

};
} // End of namespace