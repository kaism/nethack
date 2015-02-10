#include <iostream>
#include <string>
#include <vector>
#include <random>
//#include <ctime>

#include "dungeonLevel.h"
#include "Enemy.h"
#include "Tiles.h"
#include "Player.h"

class XMLSerializable;

DungeonLevel::DungeonLevel() {

}

DungeonLevel::DungeonLevel(int height, int width, mt19937 &mt) {

	kheight = height;
	kwidth = width;

	// Initialize the blank vector
	m_vvTiles.resize(kheight);

	for(auto it = m_vvTiles.begin();
		it != m_vvTiles.end();
		it++ )
	{
		(*it).resize(kwidth, ' ');
	}

	// We're going to divide the level into 4x2 chunks
	int iChunkWidth = kwidth / 4;
	int iChunkHeight = kheight / 2;


	// The strategy here is to first draw a loop of tunnels on
	// the level, and then draw rooms on top of them.

	// Taking the easy way out, and generating
	// a loop of tunnels first to drop rooms on to

	for( int x = (iChunkWidth/2); x <= ((3 * iChunkWidth) + (iChunkWidth/2)); x++ )
	{

		m_vvTiles[iChunkHeight/2][x] = '#';

		m_vvTiles[iChunkHeight + (iChunkHeight/2)][x] = '#';
	}

	for( int y = (iChunkHeight/2); y <= (iChunkHeight + (iChunkHeight/2)); y++ )
	{
		m_vvTiles[y][iChunkWidth/2] = '#';
		m_vvTiles[y][(3 * iChunkWidth) + (iChunkWidth/2)] = '#';
	}

	// Pick rooms for the up and down stairs
	int iUpXChunk = mt() % 4;
	int iUpYChunk = mt() % 2;

	int iDownXChunk = mt() % 4;
	int iDownYChunk = mt() % 2;

	// Put them in different rooms...

	while( iUpXChunk == iDownXChunk && iUpYChunk == iDownYChunk )
	{
		iDownXChunk = mt() % 4;
		iDownYChunk = mt() % 2;
	}


	// So then we iterate through the chunks, and we
	// have individual blocks of the level which don't
	// overlap, so we're going to drop a room on each one.

	for( int iXChunk = 0; iXChunk < 4; iXChunk++ )
	{
		int iXStart = iXChunk * iChunkWidth;

		for( int iYChunk = 0; iYChunk < 2; iYChunk++ )
		{
			int iYStart = iYChunk * iChunkHeight;

			// Ok, so here we get a bit shifty.
			// We have 8 chunks.  We need to have 
			// at minimum 200 room tiles.  200/8 is
			// 25.  sqrt(25) is 5.  So we're going
			// to generate rooms of minimum size 5x5.

			int iRoomWidth = (mt() % (iChunkWidth - 5)) + 5;
			int iRoomHeight = (mt() % (iChunkHeight - 5)) + 5;

			// Randomly calculate the offset of the randomly
			// sized rood

			int iXOffset = mt() % (iChunkWidth - iRoomWidth);
			int iYOffset = mt() % (iChunkHeight - iRoomHeight);

			// Make sure this room lines up with the pre-generated
			// tunnels

			int iTunnelY = iYStart + (iChunkHeight/2);


			// Verify that the room matches the tunnel in the Y direction
			if( iYOffset + iYStart > iTunnelY )
			{
				iYOffset = iTunnelY - iYStart;
			}
			else if( iYOffset + iYStart + iRoomHeight <= iTunnelY )
			{
				iYOffset = 1 + iTunnelY - (iYStart + iRoomHeight);
			}

			// And check for the X direction (although this only matters for
			// rooms in the first or last chunk, X-wise)

			if( iXChunk == 0 || iXChunk == 3 )
			{
				int iTunnelX = iXStart + (iChunkWidth/2);

				if( iXOffset + iXStart > iTunnelX )
				{
					iXOffset = iTunnelX - iXStart;
				}
				else if( iXOffset + iXStart + iRoomWidth <= iTunnelX )
				{
					iXOffset = 1 + iTunnelX - (iXStart + iRoomWidth);
				}

			}

			// And then put the generated room on the level

			for( int x = 0; x < iRoomWidth; x++ )
			{
				for( int y = 0; y < iRoomHeight; y++ )
				{
					m_vvTiles[y + iYOffset + iYStart][x + iXOffset + iXStart] = '.';
				}
			}

			// Check to see if we picked this room for up/down stairs, and
			// if so, randomly place the stairs

			if( iXChunk == iUpXChunk && iYChunk == iUpYChunk )
			{
				x_up = iXOffset + iXStart + (mt() % iRoomWidth);
				y_up = iYOffset + iYStart + (mt() % iRoomHeight);
				m_vvTiles[y_up][x_up] = '<';
				d_up = m_vvTiles[y_up][x_up];
			}

			if( iXChunk == iDownXChunk && iYChunk == iDownYChunk )
			{
				x_down = iXOffset + iXStart + (mt() % iRoomWidth);
				y_down = iYOffset + iYStart + (mt() % iRoomHeight);
				m_vvTiles[y_down][x_down] = '>';
				d_down = m_vvTiles[y_down][x_down];
			}

		}
	}

	char_to_tiles();
}

//For testing
void DungeonLevel::dump() {

	tiles_to_char();

	for(int i = 0; i < kheight; i++) {
		for(int j = 0; j < kwidth; j++) {
			cout << kcharTiles[i][j];
		}
		cout << endl;
	}
}

void DungeonLevel::setTilesXY(char t, bool p, int x, int y) {

	ktiles[y][x].setTiles(t);
	ktiles[y][x].setPassable(p);
}

void DungeonLevel::char_to_tiles() {

	vector<Tiles> v;
	Tiles tileRoom;
	Tiles notPassable(' ', false);
	Tiles upstairs('>', true);
	Tiles downstairs('<', true);
	Tiles tunnel('#', true);

	for(int i = 0; i < kheight; i++) {
		ktiles.push_back(v);
		for(int j = 0; j < kwidth; j++) {
			if(m_vvTiles[i][j] == '.')
				ktiles[i].push_back(tileRoom);
			else if(m_vvTiles[i][j] == '#')
				ktiles[i].push_back(tunnel);
			else if(m_vvTiles[i][j] == '>')
				ktiles[i].push_back(upstairs);
			else if(m_vvTiles[i][j] == '<')
				ktiles[i].push_back(downstairs);
			else
				ktiles[i].push_back(notPassable);
		}
	}
}

void DungeonLevel::tiles_to_char() {

	vector<char> v;

    for(int i = 0; i < kheight; i++) {
    kcharTiles.push_back(v);
       for(int j = 0; j < kwidth; j++)  {

            kcharTiles[i].push_back(ktiles[i][j].getTiles());
        }
     }


	// for(int i = 0; i < Y; i++) {

	// 	char *pchar = NULL;

	// 	for(int j= 0; j < X; j++)  {

	// 		pchar += ktiles[i][j]->getTiles();
	// 	}
		
	// 	kcharTiles.push_back(*pchar);
	// }
}

void DungeonLevel::setLevel(int level) {

	klevel = level;
}

int DungeonLevel::getLevel() {

	return klevel;
}

Tiles DungeonLevel::at(int x, int y)
{
	return ktiles[y][x];
}

char DungeonLevel::atchar(int x, int y) {

	//tiles_to_char();

	//return kcharTiles[y][x];
	return m_vvTiles[y][x];
}


void DungeonLevel::getUpstairs(int &x, int &y) {

	x = x_up;
	y = y_up;
}

void DungeonLevel::getDownstairs(int &x, int &y) {

	x = x_down;
	y = y_down;
}

void DungeonLevel::setPlayerTile(Player *player) {

	ktiles[player->y()][player->x()].setTiles(*player->getSymbol().c_str());
	ktiles[player->y()][player->x()].setPassable(false);

	kplayer = player;
}

// void DungeonLevel::setEnemyTile(Enemy *enemy) {

// 	ktiles[enemy->y()][enemy->x()].setTiles(*enemy->getSymbol().c_str());
// 	ktiles[enemy->y()][enemy->x()].setPassable(false);
// }

int DungeonLevel::getWidth()
{
	return ktiles[0].size();
}

int DungeonLevel::getHeight()
{
	return ktiles.size();
}

bool DungeonLevel::passable(int x, int y) {

	if(ktiles[y][x].getPassable() == true)
		return true;
	else
		return false;
}

void DungeonLevel::setEnemy(Enemy* enemy) {

	kenemy = enemy;
	//setEnemyTile(kenemy);
}

Enemy* DungeonLevel::getEnemy() {

	return kenemy;
}

void DungeonLevel::setPlayer(Player *player) {

	kplayer = player;
	//setPlayerTile(kplayer);
}

void DungeonLevel::setConsumables(Consumables* consume) {

	kconsume = consume;
}

Consumables* DungeonLevel::getConsumables() {

	return kconsume;
}

void DungeonLevel::setArmor(Armor *newArmor) {

    karmor = newArmor;
}

Armor* DungeonLevel::getArmor() {

    return karmor;
}

void DungeonLevel::setWeapon(Weapon *newWeapon) {

    kweapon = newWeapon;
}

Weapon* DungeonLevel::getWeapon() {

    return kweapon;
}

// template<class &T, class &V>
// DungeonLevel::getXY(Unit &unit) {

// 	return getXY<T, V>(unit.x(), unit.y());
// }
