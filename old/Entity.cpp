#include <string>
#include <fstream>
#include <iostream>

#include "Entity.h"

using namespace std;

Entity::Entity() {

	kname = "Niall";
	ksymbol = '&';
}

Entity::Entity(string name, string symbol) {

	kname = name;
	ksymbol = symbol;
}

string Entity::getName() const {

		return kname;
}

void Entity::setName(string name) {

	kname = name;
}

void Entity::setSymbol(string symbol) {

	ksymbol = symbol;
}

string Entity::getSymbol() {

	//return sym_to_char().c_str();
	return ksymbol;
}

// string Entity::sym_to_char() {
// 	return ksymbol;
// }

int Entity::derivedType() {

	return 0;
}

int Entity::x() {

	return kx;
}

void Entity::setx(int w) {

	kx = w;
}

int Entity::y() {

	return ky;
}

void Entity::sety(int z) {

	ky = z;
}

string Entity::adjacent(Entity *entity) {

}

void Entity::dumpObject(){

	cout << "Entity: " << endl;

	dumpObjectData();
}

void Entity::dumpObjectData() {

	cout << "		  Name: " << getName() << endl;
	cout << "DisplaySymbol:" << getSymbol() << endl;
}

void Entity::writeFragment(ostream &output) {

	output << "<Entity>" << endl;

	writeDataAsFragment(output);

	output << "</Entity>" << endl;
}

void Entity::writeDataAsFragment(ostream &output) {

	output << "<name>" << getName() << "</name>" << endl;
	output << "<symbol>" << getSymbol() << "</symbol>" << endl;
}

void Entity::setElementData(string sElementName, string sValue) {

	if(sElementName == "name")
		setName(sValue);
	else if(sElementName == "symbol")
		setSymbol(sValue);

}
