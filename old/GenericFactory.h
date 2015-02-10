#ifndef _GenericFactory_included_
#define _GenericFactory_included_

#include "Enemy.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "parser.h"

#include <vector>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <random>

using namespace std;

template<class T>
class GenericFactory
{
public:	
	static GenericFactory & instance(std::string sFilename)
	{
       		static GenericFactory<T> factory(sFilename);

	        return factory;
	}

	virtual ~GenericFactory()
	{
	}

	T * generate()
	{
		if( m_vObjects.size() == 0 )
		{
			return NULL;
		}

		// Note! You may want to implement a copy() method in XMLSerializable 
		// to avoid slicing here (and to allow a GenericFactory<Item> to work
		// correctly -- and use it here instead of calling the copy constructor
		// explicity.
		return dynamic_cast<T*>(m_vObjects[randomValue(m_vObjects.size())]->copy());

	}


	static int randomValue(int iMax)
	{
        	static std::mt19937 mt(time(NULL));
       		return mt() % iMax;
	}

private:
	GenericFactory(std::string sFilename)
	{
	        std::vector<XMLSerializable*> vObjects;

	        std::map<std::string, std::function<XMLSerializable*()>> mapConstructor;

	        //mapConstructor["Entity"] = []() { return new Entity; };
				mapConstructor["Item"] = []() { return new Item; };
					//mapConstructor["Consumables"] = []() { return new Consumables; };
					mapConstructor["Armor"] = []() { return new Armor; };
					mapConstructor["Weapon"] = []() { return new Weapon; };
				//mapConstructor["Unit"] = []() { return new Unit; };
					//mapConstructor["Player"] = []() { return new Player; };
					mapConstructor["Enemy"] = []() { return new Enemy; };
	

	        parseXML(mapConstructor, sFilename, vObjects);

	        for( XMLSerializable * pObject : vObjects )
	        {
			T * pT = dynamic_cast<T*>(pObject);

       	         	if( pT )
	                {
				m_vObjects.push_back(pT);
			}
		}
	}

	std::vector<T*> m_vObjects;
};

#endif
