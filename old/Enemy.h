#ifndef ENEMY_H
#define ENEMY_H

#include <fstream>
#include <string>

#include "Unit.h"
class Player;

class Enemy : public Unit {

	public:
		Enemy();
		Enemy(bool hostile, int rating, int level, int hp, string name, string symbol);

		virtual bool takeTurn();
		virtual void attack(Player *player);

		virtual bool getHostility() const;
		virtual void setHostility(bool hostile);
		virtual int getcr();
		virtual void setcr(int rating);
		// virtual void setCurWeapon(Weapon &weapon);
		// virtual Weapon getCurWeapon();
		// virtual void setCurArmor(Armor &armor);
		// virtual Armor getCurArmor();

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

	/* k for klass */
		
	private:
		bool khostile;
		int cr;
};

#endif