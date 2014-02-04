#include "Cart_Vector.h"

Cart_Vector::Cart_Vector( )
{
	x=0.0;
	y=0.0;
}
Cart_Vector::Cart_Vector(double inputx,double inputy)
{
	x=inputx;
	y=inputy;
}
Cart_Point operator+(const Cart_Point &p, const Cart_Vector &v)
{
	return Cart_Point(p.x+v.x,p.y+v.y );
}
Cart_Vector operator-(const Cart_Point &p1,const Cart_Point &p2)
{
	return Cart_Vector( p1.x-p2.x,p1.y-p2.y ) ;
}
Cart_Vector operator*(Cart_Vector &v, double d)
{
	return Cart_Vector( d*v.x , d*v.y);
}
Cart_Vector operator/(Cart_Vector &v, double d)
{
	//asume d is non-zero
	return Cart_Vector(v.x /d , v.y /d);
}
ostream & operator<<( ostream &os,Cart_Vector v)
{
	os<<"<"<<v.x<<","<<v.y<<">";
	return os;
} 