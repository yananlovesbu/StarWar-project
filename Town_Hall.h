#ifndef _TOWN_HALL_H
#define _TOWN_HALL_H

#include "Cart_Point.h"
#include "Game_Object.h"
class Town_Hall:public Game_Object
{
public:
	Town_Hall( );
	Town_Hall( int inputId, Cart_Point inputLoc);
	void deposit_gold( double deposit_amount );
	bool update( );
	void show_status( );
	~Town_Hall();
	void save(ofstream &file);
	void restore(ifstream &file, Model &model );
private:
	double amount;	//the amount of current gold
}; 

#endif