#include <string>
#include <fstream>
#include <iostream>

#include "Weapon.h"

using namespace std;

Weapon::Weapon() {

	kdamage = 0;
	ktype = "puncture";
}

Weapon::Weapon(int damage, string type, bool drop, int weight, int value, int quantity, string name, string symbol)
        : Item(drop, weight, value, quantity, name, symbol) {

	kdamage = damage;
	ktype = type;
}

void Weapon::setDamage(int damage) {

	kdamage = damage;
}

int Weapon::getDamage() const {

	return kdamage;
}

void Weapon::setType(string type) {

	ktype = type;
}

string Weapon::getType() const {

	return ktype;
}

// void Weapon::use(Unit *user) {

// 	dynamic_cast<Player*>(user);

// 	user->setCurWeapon();	
// }

void Weapon::dumpObject() {

	cout << "Weapon: " << endl;

	dumpObjectData();
}

void Weapon::dumpObjectData() {

	Item::dumpObjectData();

	cout << "  Type: " << getType() << endl;
	cout << "Damage: " << getDamage() << endl;

}

void Weapon::writeFragment(ostream &output) {

	output << "<Weapon>" << endl;

	writeDataAsFragment(output);

	output << "</Weapon>" << endl;
}

void Weapon::writeDataAsFragment(ostream &output) {

	Item::writeDataAsFragment(output);

	output << "<type>" << getType() << "</type>" << endl;
	output << "<damage>" << getDamage() << "</damage>" << endl;
}

void Weapon::setElementData(string sElementName, string sValue) {

	Item::setElementData(sElementName, sValue);

	if(sElementName == "damage")
		setDamage(atoi(sValue.c_str()));
	else if(sElementName == "type")
		setType(sValue);
}
