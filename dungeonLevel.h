#ifndef DUNGEONLEVEL
#define DUNGEONLEVEL

#include <vector>
#include <random>

using namespace std;

class dungeonLevel {

	public:
		dungeonLevel();
		dungeonLevel(int height, int width, mt19937 &mt);
        void dump();

	private:
		int c_height;
		int c_width;

		int x_up;
		int y_up;

		int x_down;
		int y_down;

		vector<vector<char> > c_dungTiles;
                        

};

#endif