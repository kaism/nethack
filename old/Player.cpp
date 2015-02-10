#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <random>

#include "Player.h"
#include "Enemy.h"
#include "Consumables.h"

using namespace std;

Player::Player() {

	kexp = 0;
	krace = "Wolf";
	ktype = "Rogue";
}

Player::Player(int ex, string race, string type, int level, int hp, string name, string symbol)
		: Unit(level, hp, name, symbol) {

	kexp = ex;
	krace = race;
	ktype = type;
    //int damage, string type, bool drop, int weight, int value, int quantity, string name, string symbol
    Weapon *weapon = new Weapon(1, "puncture", false, 1, 0, 1, "sword", "{");
    //string type, int protection, int dexBonus, bool drop, int weight, int value, int quantity, string name, string symbol
    Armor *armor = new Armor("mithral", 4, 6, false, 2, 0, 1, "chainmail", "=");
	this->setCurWeapon(weapon);
	this->setCurArmor(armor);

	// inventory.push_back(weapon);
	// inventory.push_back(armor);
}

void Player::setExp(int ex) {

	kexp = ex;
}

int Player::getExp() const {

	return kexp;
}

void Player::setRace(string race) {

	krace = race;
}

string Player::getRace() const {

	return krace;
}

void Player::setType(string type) {

	ktype = type;
}

string Player::getType() const {

	return ktype;
}

int Player::derivedType() {

	return 3;
}

// void Player::use(Item* item) {
	
// 	item->use(this);
// }

void Player::attack(Enemy *enemy) {

	mt19937 mt;
	mt.seed( time(NULL) );

	static int damage = mt() % 3;

	damage += this->getCurWeapon()->getDamage();

	if(enemy->getCurArmor()->getProtection() < damage)
		enemy->sethp( enemy->gethp() + (enemy->getCurArmor()->getProtection() - damage) );
}

void Player::heal() {

	static int count;
	count++;
	if(gethp() <= 20) {
		if(count == 5) {
			sethp( gethp() + 1);
			count = 0;
		}
	}
}

// void Player::setCurArmor(Armor *newArmor) {

// 	karmor = newArmor;
// }

// Armor* Player::getCurArmor() {

// 	return karmor;
// }

// void Player::setCurWeapon(Weapon *newWeapon) {

// 	kweapon = newWeapon;
// }

// Weapon* Player::getCurWeapon() {
// 	return kweapon;
// }

// Item* Player::getCurItem() {

// }

void Player::decrHealth(int damage) {

	sethp( gethp() - (damage - getCurArmor()->getProtection()) );
}

void Player::incrHealth(Consumables *consume) {

	sethp( gethp() + consume->getHealth());

}

void Player::addWeapon(Weapon &weapon) {

}

void Player::addArmor(Armor &armor) {

}

void Player::removeFromInv(Item* item) {

	// vector<Item*> newInv;

	// for(auto elem : inventory)
	// 	if(elem != item)
	// 		newInv.push_back(elem);

	// inventory = newInv;

}

void Player::addToInv(Item *item) {

	// for(auto elem : inventory)
	// 	if(item->getName() == elem->add())
	// 		;//...
}

void Player::dumpObject() {

	cout << "Player: " << endl;

	dumpObjectData();
}


void Player::dumpObjectData() {

	Unit::dumpObjectData();

	cout << "Type: " << getType() << endl;
	cout << "Race: " << getRace() << endl;
	cout << " Exp: " << getExp() << endl;
}

void Player::writeFragment(ostream &output) {

	output << "<Player>" << endl;

	writeDataAsFragment(output);

	output << "</Player>" << endl;
}

void Player::writeDataAsFragment(ostream &output) {

	Unit::writeDataAsFragment(output);

	output << "<exp>" << getExp() << "</exp>" << endl;
	output << "<race>" << getRace() << "</race>" << endl;
	output << "<type>" << getType() << "</race>" << endl;
}

void Player::setElementData(string sElementName, string sValue) {

	Unit::setElementData(sElementName, sValue);

	if(sElementName == "exp")
		setExp(atoi(sValue.c_str()));
	else if(sElementName == "race")
		setRace(sValue);
	else if(sElementName == "type")
			setType(sValue);
}
