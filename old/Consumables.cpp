#include <fstream>
#include <string>
#include <iostream>

#include "Unit.h"
#include "Consumables.h"
#include "Item.h"
#include "Entity.h"

using namespace std;

Consumables::Consumables() {

	khealth = 2;
}

Consumables::Consumables(int health, bool drop, int weight, int value, int quantity, string name, string symbol)
        : Item(drop, weight, value, quantity, name, symbol) {

	khealth = health;
}

void Consumables::use(Unit *user) {

	Player* pl = dynamic_cast<Player*>(user);

	pl->sethp( pl->gethp() + khealth );
}

void Consumables::setHealth(int health) {

	khealth = health;
}


int Consumables::getHealth() const {

	return khealth;
}

void Consumables::dumpObject(){

	cout << "Consumables: " << endl;

	dumpObjectData();
}

void Consumables::dumpObjectData() {

	Item::dumpObjectData();

	cout << "	Health: " << getHealth() << endl;
}

void Consumables::writeFragment(ostream &output) {

	output << "<Consumables>" << endl;

	writeDataAsFragment(output);

	output << "</Consumables>" << endl;
}

void Consumables::writeDataAsFragment(ostream &output) {

	Item::writeDataAsFragment(output);

	output << "<health>" << getHealth() << "</health>" << endl;
}

void Consumables::setElementData(string sElementName, string sValue) {

	Item::setElementData(sElementName, sValue);

	if(sElementName == "health")
		setHealth(atoi(sValue.c_str()));
}
