#ifndef _MODEL_H
#define _MODEL_H
#include <list>
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "View.h"
#include "Input_Handling.h"

using namespace std;

class Person;
class Miner;
class Soldier;
class Inspector;


class Model
{
public:
	Model( );
	~Model( );
	Person * get_Person_ptr(int id);
	Gold_Mine * get_Gold_Mine_ptr(int id);
	Town_Hall * get_Town_Hall_ptr(int id);
	bool update( );
	void display( View &view);
	void show_status( );
	void handle_new_command(char type, int in_id,Cart_Point in_loc );
	list<Gold_Mine *> get_Gold_Mine_list( );
	void save(ofstream & file );
	void restore( ifstream&file);
protected:
private:
	Model(Model &);
	int time;//the simulation time
	list<Game_Object *>object_ptrs;
	list<Game_Object *>active_ptrs;
	list<Person *> person_ptrs;
	list<Gold_Mine *>mine_ptrs;
	list<Town_Hall *>hall_ptrs;
};
#endif