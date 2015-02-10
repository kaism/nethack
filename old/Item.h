#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <fstream>

#include "Entity.h"
#include "Unit.h"

using namespace std;

class Item : public Entity {
	
	public:
		Item();
        Item(bool drop, int weight, int value, int quantity, string name, string symbol);

		virtual void setWeight(int weight);
		virtual int getWeight();

		virtual void setValue(int value);
		virtual int getValue();

		virtual void setQuantity(int quantity);
		virtual int getQuantity();

        virtual bool getDrop();
        virtual void setDrop(bool drop);

		//virtual void use(Unit *user);

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

		virtual Item* copy() {return new Item(*this); }

		/* k for klass */

	private:
		int kweight;
		int kvalue;
		int kquantity;
        bool kdrop;
};

#endif
