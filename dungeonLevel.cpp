#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "dungeonLevel.h"

dungeonLevel::dungeonLevel() {

}

dungeonLevel::dungeonLevel(int height, int width, mt19937 &mt) {

	c_height = height;
	c_width = width;

	c_dungTiles.resize(c_height);

	for(auto it = c_dungTiles.begin();
		it != c_dungTiles.end();
		it++ )
	{
		(*it).resize(c_width, ' ');
	}
        
        int chunkWidth = c_width / 4;
        int chunkHeight = c_height / 2;
        
        for(int x = (chunkWidth / 2); x <= ((3 * chunkWidth) + (chunkWidth / 2)); x++) {
           
           c_dungTiles[chunkHeight / 2][x] = '#';
           c_dungTiles[chunkHeight + (chunkHeight/2)][x] = '#';
        }
        
        for(int y = (chunkHeight / 2); y <= (chunkHeight + ( chunkHeight / 2 )); y++) {
           
           c_dungTiles[y][chunkWidth / 2] = '#';
           c_dungTiles[y][3*chunkWidth + (chunkWidth / 2)] = '#';
        }
   //    /* 
        int upXchunk = mt() % 4;
        int upYchunk = mt() % 2;

        int downXchunk = mt() % 4;
        int downYchunk = mt() % 2;
        
        while( upXchunk == downXchunk && upYchunk == downYchunk ) {
           
           downXchunk = mt() % 4;
           downYchunk = mt() % 2;
        }
        
        for(int xChunk = 0; xChunk < 4; xChunk++) {
           
           int xStart = xChunk * chunkWidth;
           
           for( int yChunk = 0; yChunk < 2; yChunk++ ) {
              
              int yStart = yChunk + chunkHeight;
           
              int roomWidth = ( mt() * (chunkWidth - 5 )) + 5;
              int roomHeight = (mt() % (chunkHeight - 5 )) + 5;
              
              int xOffset = mt() % (chunkWidth - roomWidth);
              int yOffset = mt() % (chunkHeight - roomHeight);
        
              int tunnelY = yStart + (chunkHeight / 2);
              
              if( yOffset = yStart > tunnelY) {
                 
                 yOffset = tunnelY - yStart;
              } else if(yOffset = yStart + roomHeight <= tunnelY ) {
                 
                 yOffset = 1 + tunnelY - (yStart + roomHeight);
              }
              
              if(xChunk == 0 || xChunk == 3) {
                 
                 int tunnelX = xStart + (chunkWidth/2);
                 
                 if(xOffset + xStart > tunnelX ) {

                 	xOffset = tunnelX - xStart;
                 
                 } else if(xOffset + xStart + roomWidth <= tunnelX) {

                 	xOffset = 1 + tunnelX - (xStart + roomWidth);
                 }
             }

             for(int x = 0; x < roomWidth; x++) {

             	for(int y = 0; y < roomHeight; y++) {

             		c_dungTiles[y + yOffset + yStart][x + xOffset + xStart] = '.';
             	}
             }

             if(xChunk == upXchunk && yChunk == upYchunk) {

             	x_up = xOffset + xStart + (mt() % roomWidth);
             	y_up = yOffset + yStart + (mt() % roomHeight);

             	c_dungTiles[y_up][x_up] = '<';
             	d_up
             }
              
   //char_to_tiles();
}

void dungeonLevel::dump() {
   
   for(int x = 0; x < c_width; x++) {
      for(int y = 0; y < c_height; y++) {
         cout << c_dungTiles[y][x];
      }
      cout << endl;
   }
}

