#ifndef DUNGEONLEVEL
#define DUNGEONLEVEL

#include <vector>
#include <random>

// #include "Tiles.h"
// #include "Player.h"
// #include "Enemy.h"
// #include "Consumables.h"
// #include "Weapon.h"
// #include "Armor.h"

class Tiles;
class Player;
class Enemy;
class Consumables;
class Weapon;
class Armor;

using namespace std;

class DungeonLevel {

	public:

		DungeonLevel();
		DungeonLevel(int height, int width, mt19937 &mt);

		Tiles at(int x, int y);
		char atchar(int x, int y);

		void setPlayer(Player& player);

		void getUpstairs(int &x, int &y);
		void getDownstairs(int &x, int &y);

		bool passable(int x, int y);

		void setTilesXY(char t, bool p, int x, int y);

		void dump();

		void char_to_tiles();

		int getWidth();
		int getHeight();

		void setLevel(int level);
		int getLevel();

		void setConsumables(Consumables* consume);
		void setEnemy(Enemy* enemy);
		void setPlayer(Player *player);

        void setWeapon(Weapon *weapon);
        Weapon* getWeapon();
        void setArmor(Armor *armor);
        Armor* getArmor();

		Enemy* getEnemy();
		Consumables* getConsumables();

		//void setEnemyTile(Enemy *enemy);
		void setPlayerTile(Player *player);

		// template<class T, class V>
		// atXY(const T& x, const V& y);

	private:

		void tiles_to_char();	
		vector<vector<char> > kcharTiles;	//For testing
		vector<vector<Tiles> > ktiles;
		vector<std::vector<char> > m_vvTiles;
		//Tiles* tiles;   ??
		
		int klevel;
		int kheight;
		int kwidth;
		char d_up;
		int x_up;
		int y_up;

		char d_down;
		int x_down;
		int y_down;

		Player *kplayer;
		Enemy* kenemy;
		Consumables *kconsume;
		Weapon *kweapon;
		Armor *karmor;
};

#endif
