#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <fstream>
// #include <vector>

#include "Entity.h"
class Weapon;
class Armor;

//#include "Condition.h"

using namespace std;

class Unit : public Entity {

	public:

		Unit();
		Unit(int level, int hp, string name, string symbol);

		virtual void attack(Unit &target);

		virtual int getlevel();
		virtual void setlevel(int level);

		virtual int gethp();
		virtual void sethp(int hp);
		virtual void setCurWeapon(Weapon *weapon);
		virtual Weapon* getCurWeapon();
		virtual void setCurArmor(Armor *armor);
		virtual Armor* getCurArmor();

		// virtual vector<Condition> getCond();
		// virtual void setCond(vector<Condition> condition);

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

		//virtual XMLSerializable* copy() {return new Unit(*this); }

		/* k for klass */

	private:
		int klevel;
		// vector<Condition> kcond;
        int khp;
		Armor *karmor;
		Weapon *kweapon;
};

#endif
