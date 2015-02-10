OBJECTS = Item.o Enemy.o Weapon.o Armor.o Entity.o Unit.o Player.o Consumables.o Game.o dungeonLevel.o tiles.o XMLSerializable.o
HEADERS = Item.h Enemy.h Weapon.h Armor.h Entity.h Unit.h Player.h Consumables.h Game.h dungeonLevel.h Tiles.h XMLSerializable.h GenericFactory.h
#CXXFLAGS = --std=c++0x


prog3: $(OBJECTS) testdungeon.o
	g++ $^ -o prog3 -lncurses -g3

%.o: %.cpp $(HEADERS)
	g++ --std=c++0x -c $< -o $@

clean:
	rm -f *.o
