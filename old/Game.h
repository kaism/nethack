#ifndef GAME_H
#define GAME_H

#include <sstream>
#include <vector>

//#include "Entity.h"
#include "Tiles.h"
#include "dungeonLevel.h"
#include "Tiles.h"
#include "Player.h"
#include "Enemy.h"
#include "Consumables.h"
#include "Weapon.h"
#include "Armor.h"

class Game {
	
	public:

		Game();
		//Game(DungeonLevel dungeon);
		//Game(Player *player, Enemy *enemy, Consumables *consume, Weapon *weapon, Armor *armor);

		//Game mechanics
		void loop();
		void playerMov();
		void enemyMov();
		string adjacent();
		bool searchAdj();
		void attack();
		void action();
		void actionListen();
		void attack(Entity *entity);
        bool over();
        void enterLevel();


		//Getters & setters
		void setDungeon(vector<DungeonLevel> &dungeon);

		void setPlayer(Player *player);
		Player* getPlayer();

		void setEnemy(vector<Enemy*> enemy);
		vector<Enemy*> getEnemy();

		void setConsumables(std::vector<Consumables*> consume);
		vector<Consumables*> getConsumables();

		void setArmor(vector<Armor*> armor);
		std::vector<Armor*> getArmor();

		void setWeapon(vector<Weapon*> weapon);
		vector<Weapon*> getWeapon();

		void setLevel();

		void utilize();

		void setTiles(Tiles *tiles);
		Tiles* getTiles();

	private:
		int kcontrol;
		int points;
		int gplace[8];
		int gfloor;
		int glevels;

		int foo;
        int bar;

		stringstream ss;
		vector<DungeonLevel> gdungeon;
		Tiles *gtiles;

		int playerx;
		int playery;

		vector<int> enemyx;
		vector<int> enemyy;

		vector<int> consumex;
		vector<int> consumey;

		vector<int> armorx;
		vector<int> armory;

		vector<int> weaponx;
		vector<int> weapony;

		// char pos;
		// size_t xpos;
		// size_t ypos;
		
		Player *gplayer;
		vector<Enemy*> genemy;
		vector<Consumables*> gconsume;
		vector<Weapon*> gweapon;
		vector<Armor*> garmor;
};

#endif
