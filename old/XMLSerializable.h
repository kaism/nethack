#ifndef _XMLSerializable_Included_
#define _XMLSerializable_Included_

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class XMLSerializable {

	public:
		virtual void dumpObject();
		virtual void dumpObjectData();
		virtual void writeFragment(ostream &output);
		virtual void writeDataAsFragment(ostream &output);
		virtual void setElementData(string sElementName, string sValue);

		virtual XMLSerializable* copy();
	private:
};

#endif
