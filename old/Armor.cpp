#include <string>
#include <fstream>
#include <iostream>

#include "Item.h"
#include "Armor.h"

using namespace std;

Armor::Armor() {

	ktype = "sword";
	kprotection = 3;
	kdexBonus = 2;
}

Armor::Armor(string type, int protection, int dexBonus, bool drop, int weight, int value, int quantity, string name, string symbol)
        : Item(drop, weight, value, quantity, name, symbol) {

	ktype = type;
	kprotection = protection;
    kdexBonus = dexBonus;
}

string Armor::getType() const {

	return ktype;
}
void Armor::setType(string type) {

	ktype = type;
}

int Armor::getProtection() const {

	return kprotection;
}

void Armor::setProtection(int protection) {

	kprotection = protection;
}

int Armor::getDexBonus() const {

	return kdexBonus;
}

void Armor::setDexBonus(int dexBonus) {

	kdexBonus = dexBonus;
}

// void Armor::use(Unit *user) {

// 		dynamic_cast<Player>(user);

// 		user->setCurArmor(this);
// }

void Armor::dumpObject() {

	cout << "Armor: " << endl;

	dumpObjectData();
}

void Armor::dumpObjectData() {

	Item::dumpObjectData();

	cout << "	   Type: " << getType() << endl;
	cout << "Protection: " << getProtection() << endl;
	cout << "  DexBonus: " << getDexBonus() << endl;
}

void Armor::writeFragment(ostream &output) {

	output << "<Armor>" << endl;

	writeDataAsFragment(output);

	output << "</Armor>" << endl;
}

void Armor::writeDataAsFragment(ostream &output) {

	Item::writeDataAsFragment(output);

	output << "<type>" << getType() << "</type>" << endl;
	output << "<protection>" << getProtection() << "</protection>" << endl;
	output << "<dexBonus>" << getDexBonus() << "</dexBonus>" << endl;
}
void Armor::setElementData(string sElementName, string sValue) {
	
	Item::setElementData(sElementName, sValue);

	if(sElementName == "protection")
		setProtection(atoi(sValue.c_str()));
	else if(sElementName == "type")
		setType(sValue);
	else if(sElementName == "dexBonus")
		setDexBonus(atoi(sValue.c_str()));
}
