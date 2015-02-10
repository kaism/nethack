#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <map>

#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Unit.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumables.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

void outputXML(vector<XMLSerializable*> &vObjects, ostream &output);

bool getClass(vector<XMLSerializable*> &vObjects, XMLSerializable* &pObject, string sLookup);

void dumpObjects(vector<XMLSerializable*> &vObjects);

void parseElement(istream & input, XMLSerializable* pObject, vector<XMLSerializable*> &vObjects)
{
	ofstream output;
	output.open("XMLoutput.xml");
	string sElementName;
	getline(input, sElementName, '>');

	bool validClass = getClass(vObjects, pObject, sElementName);

	bool bDone = false;

	string sContent;

	while( !bDone )
	{

		char c = input.get();

		if( c == '<' )
		{
			if( input.peek() == '/' )
			{
				string sEndTag;
				getline(input, sEndTag, '>');

				if( sEndTag == "/" + sElementName )
				{ 

					if(pObject != NULL) {

						pObject->setElementData(sElementName, sContent);
						outputXML(vObjects, output);
						dumpObjects(vObjects);
					}

					bDone = true;
				}
				else
				{
					cout << "Inavlid XML!" << endl;
					return;
				}
			}
			else
			{
				parseElement(input, pObject, vObjects);
			}
		}
		else if( c != '\n' )
		{
			sContent.push_back(c);
		}
	}
	output.close();
}

void parseXML(istream & input, vector<XMLSerializable*> vObjects)
{
	while(input.get() != '<')
	{
	}

	if( input.get() != '?' )
	{
		cout << "Invalid header" << endl;
		return;
	}

	while( input.get() != '?')
	{
	}


	if( input.get() != '>')
	{
                cout << "Invalid header" << endl;
                return;
	}

	while(input.get() != '<')
	{
	}

	parseElement(input, NULL, vObjects);
}

void outputXML(vector<XMLSerializable*> &vObjects, ostream &output) {

	output << "<?xml version = \" 1.0 \" encoding=\"utf-9\">" << endl << "<World>" << endl;

	for(XMLSerializable *pObject : vObjects) {
		pObject->writeFragment(output);
	}

	output << "</World>" << endl;
}

void dumpObjects(vector<XMLSerializable*> &vObjects) {

	for(XMLSerializable *xmlObjPtr : vObjects) {

		xmlObjPtr->dumpObject();
		cout << endl;
	}
}

bool getClass(vector<XMLSerializable*> &vObjects, XMLSerializable* &pObject, string sLookup) {

	map<string, function<XMLSerializable*()>> mapConstructor;

	mapConstructor["Entity"] = []() { return new Entity; };
		mapConstructor["Item"] = []() { return new Item; };
			mapConstructor["Consumables"] = []() { return new Consumables; };
			mapConstructor["Armor"] = []() { return new Armor; };
			mapConstructor["Weapon"] = []() { return new Weapon; };
		mapConstructor["Unit"] = []() { return new Unit; };
			mapConstructor["Player"] = []() { return new Player; };
			mapConstructor["Enemy"] = []() { return new Enemy; };


	function<XMLSerializable*()> pFunc = mapConstructor[sLookup];


	if(pFunc == NULL) {
		return false;
	} else {
		cout << "Success!" << endl;
		pObject = pFunc();
		vObjects.push_back(pObject); 
		return true;
	}
}	

int main(int argc, char * argv[])
{

	string sFilename;
	cout << "What file should we read? ";
	cin >> sFilename;

	ifstream input;
	input.open(sFilename.c_str());

	vector<XMLSerializable*> vObjects;

	parseXML(input, vObjects);

	return 0;
}
