#include <iostream>
#include <map>
#include <string>
#include <functional>

#include "Item.h"
#include "Enemy.h"
#include "Armor.h"
#include "Weapon.h"
#include "XMLSerializable.h"

using namespace std;

int main(int argc, char* argv[]) {

	map<string, function<XMLSerializable*()>> mapConstructor;

	mapConstructor["Item"] = []() { return new Item; };
	mapConstructor["Enemy"] = []() { return new Enemy; };
	mapConstructor["Armor"] = []() { return new Armor; };
	mapConstructor["Weapon"] = []() { return new Weapon; };

	string sLookup;

	cout << "Enter a class: ";
	cin >> sLookup;

	function<XMLSerializable*()> pFunc = mapConstructor[sLookup];

	if(pFunc == NULL) {

		cout << "NULL dur dur" << endl;

	} else {

		cout << "Success" << endl;

	}
}

