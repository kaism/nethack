#ifndef TILE_H
#define TILE_H

class Player;
class Enemy;

class Tiles {
	
	public:

		Tiles();
		Tiles(char tile, bool passable);
		char getTiles();
		void setTiles(char symbol);
		bool compare(Tiles tiles);
		void setequal(Tiles t);

		bool getPassable();
		void setPassable(bool pass);

		int x();
		void setx(int w);

		int y();
		void sety(int z);

		bool operator==(const Tiles) const;
		bool operator!=(const Tiles) const;

	private:

		char ktile;
		bool kpassable;
		// Player* player;
		// Enemy* enemy;
		int kx;
		int ky;
};

#endif