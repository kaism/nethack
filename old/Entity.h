#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <fstream>

#include "XMLSerializable.h"

using namespace std;

class Entity {

	public:

		Entity();
		Entity(string name, string symbol);
		Entity(int x, int y);

		virtual void setName(string name);
		virtual string getName() const;

		virtual void setSymbol(string symbol);
		virtual string getSymbol();

		virtual string adjacent(Entity *entity);

		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

		virtual int derivedType();

		virtual int x();
		virtual void setx(int w);

		virtual int y();
		virtual void sety(int z);

		//virtual XMLSerializable* copy() {return new Entity(*this); }

	/* k for klass */

	private:
		//string sym_to_char();
		string kname;
		string ksymbol;
		int kx;
		int ky;
};

#endif
