#ifndef _CART_VECTOR_H
#define _CART_VECTOR_H
#include <iostream>
#include "Cart_Point.h"
using namespace std;

class Cart_Vector
{
public:
	Cart_Vector( );
	Cart_Vector(double inputx,double inputy);
public:
	double x;
	double y;
};
Cart_Point operator+(const Cart_Point &p, const Cart_Vector &v);
Cart_Vector operator-(const Cart_Point &p1,const Cart_Point &p2);
Cart_Vector operator*(Cart_Vector &v, double d);
Cart_Vector operator/(Cart_Vector &v, double d);
ostream & operator<<( ostream &os,Cart_Vector v);
#endif