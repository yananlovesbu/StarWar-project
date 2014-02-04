#include <iostream>
#include <iomanip>
#include "View.h"
#include "Cart_Vector.h"
using namespace std;

View::View( ):oringin()
{
	size=11;
	scale=2.0;
}
void View::clear()
{
	for (int i=0;i<view_maxsize;i++)
		for (int j=0;j<view_maxsize;j++)
		{
			grid[i][j][0]='.';
			grid[i][j][1]=' ';
		}
}
void View::draw()
{
	ostream::fmtflags old=cout.flags();
	int num=view_maxsize;
	for (int i=size-1;i>=0;i--)
	{
		if (!(i%2))
		{
			cout<<left;
			cout<<setw(2)<<num;
			num-=4;
		}else
			cout<<"  ";
		for ( int j=0;j<size;j++)
		{
				cout<<grid[j][i][0]<<grid[j][i][1];	
		}
		cout<<"\n";
	}
	cout<<"  ";
	for (num=0;num<=view_maxsize;num+=4)
	{
		cout<<left;
		cout<<setw(4)<<num;
	}
	cout<<endl;
	cout.flags(old);
}
void View::plot(Game_Object * ptr)
{
	int x,y;
	if (get_subscripts(x,y,ptr->get_location()))
	{
		if (grid[x][y][0]=='.'&&grid[x][y][1]==' ')
		{
			ptr->drawself( grid[x][y] );
		}
		else
		{
			grid[x][y][0]='*';
			grid[x][y][1]=' '; 
		}
	}
}
bool View::get_subscripts(int &ix, int &iy, Cart_Point location)
{
	Cart_Vector v=(location-oringin)/scale;
	ix=(int)v.x;
	iy=(int)v.y;
	if (ix<0||ix>=view_maxsize||iy<0||iy>=view_maxsize)
	{
		cout<<"An object is outside the display"<<endl;
		return false;
	}
	return true;
}