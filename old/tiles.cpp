#include "Tiles.h"

Tiles::Tiles() {

	ktile = '.';
	kpassable = true;
}

Tiles::Tiles(char tile, bool passable) {

	ktile = tile;
	kpassable = passable;
}

bool Tiles::getPassable() {

	return kpassable;
}

void Tiles::setPassable(bool pass) {

	kpassable = pass;
}

char Tiles::getTiles() {

	return ktile;
}

void Tiles::setTiles(char symbol) {

	ktile = symbol;
}

bool Tiles::compare(Tiles tiles) {

	if((ktile == tiles.getTiles()) && (kpassable == tiles.getPassable()))
		return true;
	else
		return false;
}

void Tiles::setequal(Tiles t) {

	this->ktile = t.ktile;
	this->kpassable = t.kpassable;
}

bool Tiles::operator==(const Tiles r) const {

	return (ktile == r.ktile && kpassable == r.kpassable);
}

bool Tiles::operator!=(const Tiles u) const {

	return (ktile != u.ktile || kpassable != u.kpassable);
}

// void Tiles::setPlayer(Player& player) {

	
// }

// void Tiles::setEnemy(Enemy& enemy) {

// }

int Tiles::x() {

	return kx;
}

void Tiles::setx(int w) {

	kx = w;
}

int Tiles::y() {

	return ky;
}

void Tiles::sety(int z) {

	ky = z;
}