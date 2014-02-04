#ifndef _PERSON_H
#define  _PERSON_H

#include "Game_Object.h"
#include "Cart_Vector.h"

class Town_Hall;
class Gold_Mine;
class Model;
class Person:public Game_Object
{
public:
	Person( );
	Person( char in_code );
	Person( char in_code, int in_id, Cart_Point in_loc );
	void start_moving( Cart_Point dest );
	void stop( );
	void show_status( );
	virtual ~Person();
	virtual void start_mining(Gold_Mine* in_mine,Town_Hall *in_home);
	bool is_alive( );
	virtual void take_hit ( int attack_strenth,Person * attack_ptr);
	virtual void start_attack( Person* target);
	virtual void start_inspecting( Model & model);
	void save(ofstream &file);
	void restore(ifstream &file, Model &model );
protected:
	bool update_location( );
	void setup_destination( Cart_Point dest );
	int health;
private:
	double speed;
	Cart_Point destination;
	Cart_Vector delta;
};

#endif