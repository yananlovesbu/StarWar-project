#ifndef _VIEW_H
#define _VIEW_H

#include "Cart_Point.h"
#include "Game_Object.h"
#include "Cart_Vector.h"

const int view_maxsize = 20;

class View
{
public:
	View( );
	void clear( );
	void plot( Game_Object * ptr);
	void draw( );


protected:
private:
	bool get_subscripts( int &ix, int &iy, Cart_Point location);
private:
	int size;//the current size of the grid to be displayed
	double scale;//the distance represented by each cell of the grid
	Cart_Point oringin;//the coordinates of the lower left-hand corner of the grid
	char grid[view_maxsize][view_maxsize][2];//hold the characters that make up the display grid
};

#endif