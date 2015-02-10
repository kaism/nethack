#include <iostream>
#include <vector>
#include <random>
#include <ctime>

#include "dungeonLevel.h"
#include "Game.h"
#include "Tiles.h"
#include "Player.h"
#include "Enemy.h"
#include "Consumables.h"

//#include "GenericFactory.h"

using namespace std;

const int X = 79;
const int Y = 20;

int main() {
	
	static mt19937 mt;
	static mt19937 nt;
	static mt19937 ot;
    static mt19937 pt;
    static mt19937 qt;
	mt.seed( time(NULL) );
	nt.seed( time(NULL) );
	vector<DungeonLevel> world;
	vector<Enemy*> vEnemy;
	vector<Consumables*> vConsume;
	vector<Armor*> vArmor;
	vector<Weapon*> vWeapon;

	Tiles tile('.', true);

	// //bool hostile, int rating, int level, int hp, string name, string symbol
	// Enemy* enemy = new Enemy(true, 1, 1, 5, "orc", "E");
	

	for(int i = 0; i < 7; i++) {
	
		DungeonLevel dungeon(Y, X, mt);

		//bool hostile, int rating, int level, int hp, string name, string symbol
		Enemy* enemy = new Enemy(true, 1, 1, 5, "orc", "E");

        //int health, bool drop, int weight, int value, int quantity, string name, string symbol
        Consumables* consume = new Consumables(1, false, 1, 0, 1, "roast beef", "*");

        Weapon* weapon = new Weapon(1, "puncture", true, 1, 0, 1, "dagger", "!");

        Armor* armor = new Armor("leather", 1, 10, true, 1, 0, 1, "leather", "%");
	
		//Enemy *enemy = GenericFactory::instance("world.xml").generate();

        int a = pt() % X;
        int b = pt() % Y;

        while( !(tile == dungeon.at(a, b)) ) {

            a = pt() % X;
            b = pt() % Y;
        }

        int c = qt() % X;
        int d = qt() % Y;

        weapon->setx(a);
        weapon->sety(b);
        dungeon.setWeapon(weapon);

        while( !(tile == dungeon.at(c, d)) ) {

            c = qt() % X;
            d = qt() % Y;
        }

        armor->setx(c);
        armor->sety(d);
        dungeon.setArmor(armor);

		int u = ot() % X;
		int v = ot() % Y;

		while( !(tile == dungeon.at(u,v)) ) {

			u = ot() % X;
			v = ot() % Y;
		}

		consume->setx(u);
		consume->sety(v);

		dungeon.setConsumables(consume);

		int w = nt() % X;
		int z = nt() % Y;
	
		//pick a spot for enemy
	
		while( !(tile == dungeon.at(w,z)) ) {
	
			w = nt() % X;
			z = nt() % Y;
		}

		enemy->setx(w);
		enemy->sety(z);

		dungeon.setEnemy(enemy);

		dungeon.setLevel(i);

		vEnemy.push_back(enemy);
		vConsume.push_back(consume);
        vWeapon.push_back(weapon);
        vArmor.push_back(armor);
		world.push_back(dungeon);
	}

	//int ex, string race, string type, int level, int hp, string name, string symbol
	Player* niall = new Player(0, "Wolf", "Rogue", 1, 20, "Niall", "N");

	int x = mt() % X;
	int y = mt() % Y;

	while( !(tile == world[0].at(x,y))) {
	
		x = mt() % X;
		y = mt() % Y;		
	}

	niall->setx(x);
	niall->sety(y);
	
	world[0].setPlayer(niall);

	Game game;

	//game.setTiles(tile);
	game.setDungeon(world);

	game.setLevel();

	game.setPlayer(niall);

	game.setEnemy(vEnemy);

	game.setConsumables(vConsume);

	game.setArmor(vArmor);

	game.setWeapon(vWeapon);

	// cout << game.getPlayer()->x() << endl << game.getEnemy()->y() << endl;
	//cout << "success" << endl;

	game.loop();

	return 0;
}
