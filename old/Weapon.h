#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <fstream>

#include "Item.h"

using namespace std;

class Weapon : public Item {
	
	public:

		Weapon();
        Weapon(int damage, string type, bool drop, int weight, int value, int quantity, string name, string symbol);

		virtual void setDamage(int damage);
		virtual int getDamage() const;

		virtual void setType(string type);
		virtual string getType() const;

		//virtual void use(Unit *user);

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

	private:

		int kdamage;
		string ktype;
};

#endif
