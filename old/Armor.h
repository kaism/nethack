#ifndef ARMOR_H
#define ARMOR_H

#include <string>
#include <fstream>

#include "Item.h"

class Armor : public Item {

	public:

		Armor();
        Armor(string type, int protection, int dexBonus, bool drop, int weight, int value, int quantity, string name, string symbol);

		virtual string getType() const;
		virtual void setType(string type);

		virtual int getProtection() const;
		virtual void setProtection(int armorBonus);

		virtual int getDexBonus() const;
		virtual void setDexBonus(int dexBonus);

		//virtual void use(Unit &user);

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

			/* k for klass */

		private:
			string ktype;
			int kprotection;
			int kdexBonus;
};

#endif
