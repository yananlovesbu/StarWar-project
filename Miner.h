#ifndef _MINER_H
#define _MINER_H

#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"

class Person;

class Miner:public Person 
{
public:
	Miner( );
	Miner( int in_id, Cart_Point in_Loc);
	bool update( );
	void start_mining(Gold_Mine* inputMine, Town_Hall* inputHome);
	void show_status( );
	~Miner();
	void save(ofstream & file );
	void restore(ifstream &file, Model &model );
private:
	double amount; //the amount of gold currently being carried
	Gold_Mine* mine;//a pointer to the Gold_Mine to be mined
	Town_Hall* home;//a pointer to the Town_Hall where the gold will be deposited
};

#endif