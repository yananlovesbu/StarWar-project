#ifndef _CART_POINT_H
#define _CART_POINT_H

#include <iostream>
using namespace std;

class Cart_Point
{
public:
	Cart_Point( );
	Cart_Point(double inputx,double inputy);
public:
	double x;
	double y;
};
double cart_distance(Cart_Point p1, Cart_Point p2);
ostream & operator<<( ostream &os,Cart_Point & p );
bool operator==( Cart_Point p1,Cart_Point p2);
#endif