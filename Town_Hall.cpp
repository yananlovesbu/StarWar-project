#include <iostream>
#include "Town_Hall.h"
using namespace std;

Town_Hall::Town_Hall( ):Game_Object('t',1,Cart_Point(0,0) )
{
	state = 'o'; //origin level
	amount =0.0;
	cout<<"Town_Hall default constructed"<<endl;
}
Town_Hall::Town_Hall( int inputId, Cart_Point inputLoc):Game_Object('t',inputId,inputLoc)
{
	display_code = 't';
	state = 'o'; //origin level
	amount =0.0;
	cout<<"Town_Hall constructed"<<endl;
}

void Town_Hall::deposit_gold( double deposit_amount )
{
	amount += deposit_amount;
}
bool Town_Hall::update( )
{
	if (amount >= 50.0 )
		if (state == 'o')
		{
			state = 'u'; //upgraded
			display_code = 'T';
			cout<<display_code<<get_id()<<" has been upgraded."<<endl;
			return true;
		}	
		return false;
}
void Town_Hall::show_status( )
{
	cout<<"Town_Hall status:";
	Game_Object::show_status();
	cout<<"    Contains "<<amount<<" of gold";
	if (state=='o')
		cout<<"    Not yet upgraded"<<endl;
	if (state=='u')
		cout<<"    Upgraded"<<endl;
}
Town_Hall::~Town_Hall()
{
	cout<<"Town_Hall destructed."<<endl;
}
void Town_Hall::save(ofstream &file)
{
	Game_Object::save(file);
	file<<amount<<' ';
}
void Town_Hall::restore(ifstream &file, Model &model )
{
	Game_Object::restore(file,model);
	file>>amount;
}