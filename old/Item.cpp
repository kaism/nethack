#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

#include "Entity.h"
#include "Unit.h"
#include "Item.h"

using namespace std;

Item::Item()
{
    kdrop = false;
	kweight = 0;
	kvalue = 0;
	kquantity = 0;
}

Item::Item(bool drop, int weight, int value, int quantity, string name, string symbol) : Entity(name, symbol) {

    kdrop = drop;
    kweight = weight;
	kvalue = value;
	kquantity = quantity;
}

void Item::setWeight(int weight) {

	kweight = weight;
}

int Item::getWeight() {

	return kweight;
}

bool Item::getDrop() {

    return kdrop;
}

void Item::setDrop(bool drop) {

    kdrop = drop;
}

void Item::setValue(int value) {

	kvalue = value;
}
	
int Item::getValue() {

	return kvalue;
}

void Item::setQuantity(int quantity) {

	kquantity = quantity;
}

int Item::getQuantity() {
	
	return kquantity;
}

// void Item::use(Unit *user) {

// }

void Item::dumpObject(){

	cout << "Item: " << endl;

	dumpObjectData();
}

void Item::dumpObjectData() {

	Entity::dumpObjectData();

	cout << "Quantity: " << getQuantity() << endl;
	cout << "	Value: " << getValue() << endl;
	cout << "  Weight: " << getWeight() << endl;
}


void Item::writeFragment(ostream &output) {

	output << "<Item>" << endl;

	writeDataAsFragment(output);

	output << "</Item>" << endl;
}

void Item::writeDataAsFragment(ostream &output) {

	Entity::writeDataAsFragment(output);

	output << "<weight>" << getWeight() << "</weight>" << endl;
	output << "<value>" << getValue() << "</value>" << endl;
	output << "<quantity>" << getQuantity() << "</quantity>" << endl;
}

void Item::setElementData(string sElementName, string sValue) {

	Entity::setElementData(sElementName, sValue);

	if(sElementName == "weight")
		setWeight(atoi(sValue.c_str()));
	else if(sElementName == "value")
		setValue(atoi(sValue.c_str()));
	else if(sElementName == "quantity")
		setQuantity(atoi(sValue.c_str()));
}
