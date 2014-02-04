#ifndef _SOLDIER_H
#define _SOLDIER_H
#include "Cart_Point.h"
#include "Cart_Vector.h"

class Person;

class Soldier:public Person
{
public:
	Soldier();
	Soldier(char in_code);
	Soldier( int in_id, Cart_Point in_loc );
	~Soldier();
	void start_attack(Person* in_target);
	void take_hit(int attack_strenth,Person * attack_ptr);
	bool update();
	void show_status();
	void save(ofstream & file );
	void restore(ifstream &file, Model &model );
protected:
private:
	int attack_strenth;
	double range;
	Person *target;
};

#endif