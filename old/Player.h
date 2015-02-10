#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fstream>
#include <vector>

#include "Unit.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"

//#include "Consumables.h"

class Consumables;
class Enemy;

class Player : public Unit {

	public:

		Player();
		Player(int ex, string race, string type, int level, int hp, string name, string symbol);

		virtual void setExp(int ex);
		virtual int getExp() const;

		virtual void setRace(string race);
		virtual string getRace() const;

		virtual void setType(string type);
		virtual string getType() const;

		virtual int derivedType();

		virtual void attack(Enemy *enemy);

		//Get current Armor, weapon, item.
		// virtual Armor* getCurArmor();
		// virtual Weapon* getCurWeapon();
		//virtual Item* getCurItem();

		//add to inventory
		virtual void addArmor(Armor &armor);
		virtual void addWeapon(Weapon &weapon);
		virtual void addToInv(Item *item);

		//Set current armor, weapon, item
		//virtual void setCurArmor(Armor *newArmor);
		// virtual void setCurWeapon(Weapon &newWeapon);
		virtual void incrHealth(Consumables *consume);
		virtual void decrHealth(int damage);
		virtual void removeFromInv(Item *item);
		//virtual void use(Item* item);

		//PC heals over time
		virtual void heal();

		// virtual void sethp(int health);
		// virtual int gethp();

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);
		
	/* k for klass */

	private:
		int kexp;
		string krace;
		string ktype;	//"type" = class (paladin, rogue, knite, etc.)
		vector<Item> inventory;
};

#endif
