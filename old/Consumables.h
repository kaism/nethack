#ifndef CONSUMABLES_H
#define CONSUMABLES_H

#include <fstream>
#include <string>

#include "Item.h"
#include "Unit.h"
#include "Player.h"

using namespace std;

class Consumables : public Item {

	public:

		Consumables();
        Consumables(int health, bool drop, int weight, int value, int quantity, string name, string symbol);

		virtual void setHealth(int health);
		virtual int getHealth() const;

		virtual void use(Unit *user);

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

		/* k for klass */

	private:
		int khealth;
};

#endif
