#include <fstream>
#include <string>
#include <random>
#include <iostream>

#include "Player.h"
#include "Unit.h"
#include "Enemy.h"

using namespace std;

Enemy::Enemy()
{
	khostile = true;
	cr = 1;
}

Enemy::Enemy(bool hostile, int rating, int level, int hp, string name, string symbol)
		: Unit(level, hp, name, symbol) {

	khostile = hostile;
	cr = rating;
    //int damage, string type, bool drop, int weight, int value, int quantity, string name, string symbol
    Weapon *weapon = new Weapon(1, "puncture", false, 1, 0, 1, "dagger", "\\");
    //string type, int protection, int dexBonus, bool drop, int weight, int value, int quantity, string name, string symbol
    Armor *armor = new Armor("light", 2, 3, false, 2, 0, 1, "chainmail", "/");
	this->setCurWeapon(weapon);
	this->setCurArmor(armor);
}

bool Enemy::takeTurn() {

	mt19937 mt;
	mt.seed( time(NULL) );
	int turn = mt() % 2;
	if(turn == 0)
		return false;
	else
		return true;
}

bool Enemy::getHostility() const {

	return khostile;
}

int Enemy::getcr() {

	return cr;
}

void Enemy::setcr(int rating) {

	cr = rating;
}

void Enemy::attack(Player *player) {

	mt19937 mt;
	mt.seed( time(NULL) );

	static int damage = mt() % 3;

	damage += this->getCurWeapon()->getDamage();

	if(player->getCurArmor()->getProtection() < damage)
		player->sethp( player->gethp() + (player->getCurArmor()->getProtection() - damage) );
}

void Enemy::setHostility(bool hostile) {

	khostile = hostile;
}

void Enemy::dumpObject(){

	cout << "Enemy: " << endl;

	dumpObjectData();
}

void Enemy::dumpObjectData() {

	Unit::dumpObjectData();

	cout << "Hostility: " << getHostility() << endl;
}

void Enemy::writeFragment(ostream &output) {

	output << "<Enemy>" << endl;

	writeDataAsFragment(output);

	output << "</Enemy>" << endl;
}

void Enemy::writeDataAsFragment(ostream &output) {

	Unit::writeDataAsFragment(output);

	output << "<hostile>" << getHostility() << "</hostile>" << endl;
}

void Enemy::setElementData(string sElementName, string sValue) {

	Unit::setElementData(sElementName, sValue);

	if(sElementName == "hostile")
		setHostility(atoi(sValue.c_str()));
}
