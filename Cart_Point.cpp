#include <cmath>
#include "Cart_Point.h"
Cart_Point::Cart_Point( )
{
	x=0.0;
	y=0.0;
}
Cart_Point::Cart_Point(double inputx,double inputy)
{
	x=inputx;
	y=inputy;
}

double cart_distance(Cart_Point p1, Cart_Point p2)
{
	return sqrt( (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) ); 
}
ostream & operator<<( ostream &os,Cart_Point & p )
{
	os<<"("<<p.x<<","<<p.y<<")";
	return os;
}
bool operator==( Cart_Point p1,Cart_Point p2)
{
	return ( (p1.x==p2.x)&&(p1.y==p2.y) );
}