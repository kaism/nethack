#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
// #include <vector>

// #include "Condition.h"
#include "Unit.h"

using namespace std;

Unit::Unit() {

	klevel = 1;
	khp = 20;
}

Unit::Unit(int level, int hp, string name, string symbol) : Entity(name, symbol) {

	klevel = level;
	khp = hp;
}

void Unit::attack(Unit &target) {

}

int Unit::getlevel() {

	return klevel;
}

void Unit::setlevel(int level) {

	klevel = level;
}

int Unit::gethp() {

	return khp;
}
void Unit::sethp(int hp) {

	khp = hp;
}

void Unit::setCurArmor(Armor *newArmor) {

	karmor = newArmor;
}

Armor* Unit::getCurArmor() {

	return karmor;
}

void Unit::setCurWeapon(Weapon *newWeapon) {

	kweapon = newWeapon;
}

Weapon* Unit::getCurWeapon() {
	
	return kweapon;
}

// vector<Condition> Unit::getCond() {

// 	return kcond;
// }

// void Unit::setCond(vector<Condition> condition) {

// 	for(int i = 0; i < condition.end(); i++)
// 		kcond[i] = condition[i];
// }

void Unit::dumpObject() {

	cout << "Unit: " << endl;

	dumpObjectData();
}

void Unit::dumpObjectData() {

	Entity::dumpObjectData();

	cout << "Level: " << getlevel() << endl;
	cout << "	HP: " << gethp() << endl;
}


void Unit::writeFragment(ostream &output) {

	output << "<Unit>" << endl;

	writeDataAsFragment(output);

	output << "</Unit>" << endl;
}

void Unit::writeDataAsFragment(ostream &output) {

	Entity::writeDataAsFragment(output);

	output << "<level>" << getlevel() << "</level>" << endl;
	output << "<hp>" << gethp() << "</hp>" << endl;
}

void Unit::setElementData(string sElementName, string sValue) {

	Entity::setElementData(sElementName, sValue);

	if(sElementName == "level")
		setlevel(atoi(sValue.c_str()));
	else if(sElementName == "hp")
		sethp(atoi(sValue.c_str()));
}
