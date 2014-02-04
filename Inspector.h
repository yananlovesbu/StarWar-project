#ifndef _INSPECTOR_H
#define _INSPECTOR_H
#include <string>
#include <list>
using namespace std;

class Person;
class Model;

class Inspector:public Person
{
public:
	Inspector( );
	Inspector(int in_id,Cart_Point in_loc,const char * in_name);
	Inspector(int in_id,Cart_Point in_loc);
	~Inspector();
	void show_status();
	bool update();
	void start_inspecting( Model & model);
	void save(ofstream & file );
	void restore(ifstream &file, Model &model );
private:
	string name;
	list<Gold_Mine* > mine_uninspected;//mines not yet inspected
	list<Gold_Mine *> mine_inspected ;//mines have been inspected on the out bound of the trip
	list<double > mine_amounts;//the amount in each mine on the outbound trip
	Cart_Point origin;
};
#endif