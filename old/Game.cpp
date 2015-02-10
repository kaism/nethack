#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <ncurses.h>

#include "Game.h"
#include "Player.h"
#include "Weapon.h"
// #include "Tiles.h"
// #include "dungeonLevel.h"
// #include "XMLSerializable.h"


class Tiles;
class dungeonLevel;
class XMLSerializable;

#define ATTACK 97
#define UTILIZE 117
#define DROP 100
#define QUIT 113

const int X = 79;
const int Y = 20;

/* 
    0 = Entity
    1 = Unit
    2 = Item
    3 = Player
    4 = Enemy
    5 = Armor
    6 = Consumables
    7 = Weapon
*/

const int ENTITY = 0;
const int UNIT = 1;
const int ITEM = 2;
const int PLAYER = 3;
const int ENEMY = 4;
const int ARMOR = 5;
const int CONSUMABLE = 6;
const int WEAPON = 7;

using namespace std;

Game::Game() {

    kcontrol = ' ';
    gfloor = 0;
    bar = 0;
}

void Game::loop() {

    //gdungeon[gfloor].dump();

    initscr();
    keypad(stdscr, TRUE);

    do {

        foo = gfloor;

        clear();

        start_color();

        use_default_colors();

        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        
        for(size_t x = 0; x < gdungeon[gfloor].getWidth(); x++) {
            for(size_t y = 0; y < gdungeon[gfloor].getHeight(); y++) {

                move(y, x);
                attron(COLOR_PAIR(2));
                addch(gdungeon[gfloor].atchar(x,y));
                attroff(COLOR_PAIR(2));
            }
        }

        move(playery, playerx);
        attron(COLOR_PAIR(3));
        addch(*gplayer->getSymbol().c_str());
        attroff(COLOR_PAIR(3));
        
        if(genemy[gfloor]->getHostility() != false) {
            move(enemyy[gfloor], enemyx[gfloor]);
            attron(COLOR_PAIR(1));
            addch(*genemy[gfloor]->getSymbol().c_str());
            attroff(COLOR_PAIR(1));
        }

        if(gconsume[gfloor]->getDrop() == true) {

            move(consumey[gfloor], consumex[gfloor]);
            attron(COLOR_PAIR(4));
            addch(*gconsume[gfloor]->getSymbol().c_str());
            attroff(COLOR_PAIR(4));
        }

        if(garmor[gfloor]->getDrop() == true) {

            move(armory[gfloor], armorx[gfloor]);
            attron(COLOR_PAIR(4));
            addch(*garmor[gfloor]->getSymbol().c_str());
            attroff(COLOR_PAIR(4));
        }

        if(gweapon[gfloor]->getDrop() == true) {

            move(weapony[gfloor], weaponx[gfloor]);
            attron(COLOR_PAIR(4));
            addch(*gweapon[gfloor]->getSymbol().c_str());
            attroff(COLOR_PAIR(4));
        }

        move(20,0);
        addstr(ss.str().c_str());

        refresh();

        kcontrol = getch();

        ss.str("");

        // if(searchAdj() == true)
        //     collision();

        playerMov();

        if(genemy[gfloor]->getHostility() != false)
            enemyMov();

        action();

        gplayer->heal();

        ss << "Level " << gfloor << " ";

    } while(!over());

    endwin();

    cout << "Player score: " << gplayer->getExp() << endl;
}

void Game::enterLevel() {

    static mt19937 mt;
    int x = mt() % X;
    int y = mt() % Y;

    if(gdungeon[gfloor].atchar(playerx, playery) == '>' ) {

        if(gfloor == 0) {
            bar = -1;
            over();
        } else
            gfloor--;

        while( !(gdungeon[gfloor].atchar(x, y) == '.') ) {

            x = mt() % X;
            y = mt() % Y;
        }

        playerx = x;
        playery = y;
        move(playery, playerx);
        addch(*gplayer->getSymbol().c_str());
        ss << "Going down! ";
    }
    if(gdungeon[gfloor].atchar(playerx, playery) == '<' && gfloor < 7) {
        gfloor++;

        while( !(gdungeon[gfloor].atchar(x, y) == '.') ) {

            x = mt() % X;
            y = mt() % Y;
        }

        playerx = x;
        playery = y;
        gdungeon[gfloor].getDownstairs(playerx, playery);
        move(playery, playerx);
        addch(*gplayer->getSymbol().c_str());
        ss << "Going up! ";
    }
}

void Game::playerMov() {



    if(kcontrol == KEY_DOWN)
    {
        if(gdungeon[gfloor].passable(playerx, playery+1) == false)
                return;
        playery++;

        enterLevel();
        
    } else if(kcontrol == KEY_UP) {

       	if(gdungeon[gfloor].passable(playerx, playery-1) == false)
       		return;
        playery--;

        enterLevel();
    
    } else if(kcontrol == KEY_LEFT) {

        if(gdungeon[gfloor].passable(playerx-1, playery) == false)
            return;
        playerx--;

        enterLevel();
        
    } else if(kcontrol == KEY_RIGHT) {

        if(gdungeon[gfloor].passable(playerx+1, playery) == false)
           	return;
        playerx++;

        enterLevel();
    
    } else  {

        ss << "Boop! ";
    }
}


void Game::enemyMov() {

    if(enemyx[gfloor] < playerx) {
        if((gdungeon[gfloor].passable(enemyx[gfloor]+1, enemyy[gfloor]) == false) || ((enemyx[gfloor]+1) == playerx))
            return;
        enemyx[gfloor]++;
    }
    
    if(enemyy[gfloor] < playery) {
        if((gdungeon[gfloor].passable(enemyx[gfloor], enemyy[gfloor]+1) == false) || ((enemyy[gfloor]+1) == playery))
            return;
        enemyy[gfloor]++;
    }
    
    if(enemyx[gfloor] > playerx) {
        if((gdungeon[gfloor].passable(enemyx[gfloor]-1, enemyy[gfloor]) == false) || ((enemyx[gfloor]-1) == playerx))
            return;
        enemyx[gfloor]--;
    }
    
    if(enemyy[gfloor] > playery) {
        if((gdungeon[gfloor].passable(enemyx[gfloor], enemyy[gfloor]-1) == false) || ((enemyy[gfloor]-1) == playery))
            return;
        enemyy[gfloor]--;
    }
}

bool Game::over() {

    if(gplayer->gethp() <= 0 || kcontrol == QUIT || bar == -1)
		return true;
	else
		return false;
}

string Game::adjacent() {

    int i;
	string str;

    int x[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int y[] = {-1, -1, -1, 0, 1, 1, 1, 0};

    for(i = 0; i <= 7; i++) {
        if( consumex[gfloor] == playerx +x[i] && consumey[gfloor] == playery+y[i] )
            str = "consume";

        if( armorx[gfloor] == playerx +x[i] && armory[gfloor] == playery+y[i] )
            str = "armor";

        if( weaponx[gfloor] == playerx +x[i] && weapony[gfloor] == playery+y[i] )
            str = "weapon";
    }

	return str;
}

bool Game::searchAdj() {

    int i;
   // int counter = 0;
    int x[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int y[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    //gplace[] = {0,0,0,0,0,0,0,0};

    bool adj = false;

    cout << "adj before loop" << endl;

    //while(counter <= 7) {
        for(i = 0; i <= 7; i++) {
            if( enemyx[gfloor] == playerx+x[i] && enemyy[gfloor] == playery+y[i] ) {
                gplace[i] = 1;
            } else {
                gplace[i] = 0;
            }
        }
      //  counter++;
   // }
    for(i = 0; i <= 7; i++) {
        if(gplace[i] == 1) {
            adj = true;
            break;
        }
    }

    gfloor = gdungeon[foo].getLevel();

    return adj;
}

void Game::attack() {


    if((gdungeon[gfloor].getEnemy()->gethp() > 0) && (gplayer->gethp() > 0)) {

         if(gdungeon[gfloor].getEnemy()->takeTurn() == true) {
            ss << "Enemy turn ";
            gdungeon[gfloor].getEnemy()->attack(gplayer);
         } else {
            ss << "Player turn ";
            gplayer->attack(genemy[gfloor]);
         }
         ss << gdungeon[gfloor].getEnemy()->gethp() << " hp: " << gplayer->gethp() << " " << gdungeon[gfloor].getEnemy()->getName() << " hp: " << gdungeon[gfloor].getEnemy()->gethp() << " ";
    }

    if(genemy[gfloor]->gethp() <= 0) {
        gplayer->setExp(gplayer->getExp() + genemy[gfloor]->getcr());
        ss << " XP: " << gplayer->getExp();
        gdungeon[gfloor].getEnemy()->setHostility(false);

        garmor[gfloor] = genemy[gfloor]->getCurArmor();
        armorx[gfloor] = genemy[gfloor]->x() + 1;
        armory[gfloor] = genemy[gfloor]->y() + 1;
        garmor[gfloor]->setDrop(true);

        gweapon[gfloor] = genemy[gfloor]->getCurWeapon();
        weaponx[gfloor] = genemy[gfloor]->x() + 1;
        weapony[gfloor] = genemy[gfloor]->y() + 1;
        garmor[gfloor]->setDrop(true);
    }

    if(gplayer->gethp() <= 0) {
        ss << "Player health less than zero ";
        over();
    }
}

void Game::utilize() {

    string adj = adjacent();

    if(adj == "consume") {

        gconsume[gfloor]->use(gplayer);
        gconsume[gfloor]->setDrop(false);
    }
    if(adj == "armor") {

        Armor* tempArmor = new Armor;
        tempArmor = gplayer->getCurArmor();

        gplayer->setCurArmor(garmor[gfloor]);

        garmor[gfloor] = tempArmor;
        armorx[gfloor] = gplayer->x() + 1;
        armory[gfloor] = gplayer->y() + 1;

        //garmor[gfloor]->use(gplayer);
    }
    if(adj == "weapon") {

        Weapon* tempWeapon = new Weapon;

        tempWeapon = gplayer->getCurWeapon();

        gplayer->setCurWeapon(gweapon[gfloor]);

        gweapon[gfloor] = tempWeapon;
        weaponx[gfloor] = gplayer->x() + 1;
        weapony[gfloor] = gplayer->y() + 1;
    }
}

void Game::action() {

    string adj;

    switch(kcontrol) {

        case ATTACK:
            
            if(searchAdj() == true) {

                attack();
            }

            break;
        case UTILIZE:

        if(searchAdj() == true) {
            ss << "Utilise ";
            utilize();
        }
            break;
        case DROP:
            ss << "Drop ";
            break;
        case QUIT:
            break;
        default:
            ;//ss << "Boop!";
    }


    //Use gplaces to pick which tile containing an entity

	//act = entity->derivedType();

	// switch(act) {

 //        case ENEMY:      //if enemy
 //            attack(entity);
 //            break;
 //        case ARMOR:     //if armor
 //            ss << "Press 'u' to utilize";
 //            cin >> foo;
 //            kcontrol = int(foo);
 //            if(kcontrol == UTILIZE) {
 //                gplayer->addArmor(dynamic_cast<Armor*>(entity));
 //                gdungeon.setTilesXY('.', true, entity->x(), entity->y());
 //            }
 //            break;

 //        case CONSUMABLE:     //consumables
 //            ss << "Press 'u' to utilize";
 //            cin >> foo;
 //            kcontrol = int(foo);
 //            if(kcontrol == UTILIZE) {
 //                gplayer->incrHealth(dynamic_cast<Consumables*>(entity));
 //                gdungeon.setTilesXY('.', true, entity->x(), entity->y());
 //            }
 //            break;
 //        case WEAPON:     //if weapon
 //            ss << "Press 'u' to utilize";
 //            cin >> foo;
 //            kcontrol = int(foo);
 //            if(kcontrol == UTILIZE) {
 //                gplayer->addWeapon(dynamic_cast<Weapon*>(entity));
 //                gdungeon.setTilesXY('.', true, entity->x(), entity->y());
 //            }
 //            break;
        
 //        default:
 //            ;//error
 //    }
}

// void Game::actionListen() {

//     char foo;
//     string adj = adjacent();

//     cin >> foo;

//     kcontrol = (int)foo;

//     switch(kcontrol) {

//         case UTILIZE:
            
//         case ATTACK:

//         case DROP:

//         case QUIT:
//     }
// }

void Game::setPlayer(Player *player) {

    gplayer = player;
    playerx = gplayer->x();
    playery = gplayer->y();
}

Player* Game::getPlayer() {

    return gplayer;
}

void Game::setEnemy(vector<Enemy*> enemy) {

    genemy = enemy;

    for(int i = 0; i < glevels; i++) {

        enemyx.push_back(genemy[i]->x());
        enemyy.push_back(genemy[i]->y());
    }
}

vector<Enemy*> Game::getEnemy() {

    return genemy;
}

void Game::setConsumables(vector<Consumables*> consume) {

    gconsume = consume;

    for(int i = 0; i < glevels; i++) {

        consumex.push_back(gconsume[i]->x());
        consumey.push_back(gconsume[i]->y());
    }
}

vector<Consumables*> Game::getConsumables() {

    return gconsume;
}

void Game::setArmor(vector<Armor*> armor) {

    garmor = armor;
    armorx.resize(glevels);
    armory.resize(glevels);
}

vector<Armor*> Game::getArmor() {

    return garmor;
}

void Game::setWeapon(vector<Weapon*> weapon) {

    gweapon = weapon;
    weaponx.resize(glevels);
    weapony.resize(glevels);
}

vector<Weapon*> Game::getWeapon() {

    return gweapon;
}


void Game::setTiles(Tiles *tiles) {

    gtiles = tiles;
}

Tiles* Game::getTiles() {

    return gtiles;
}

void Game::setDungeon(vector<DungeonLevel> &dungeon) {

    gdungeon = dungeon;
}

void Game::setLevel() {

    glevels = gdungeon.size();
}
