#include <iostream>
#include "Gold_Mine.h"
#include "Model.h"

using namespace std;

Gold_Mine::Gold_Mine( ):Game_Object('G')
{
	state = 'f'; //full
	amount = 100.0;
	cout<<"Gold_Mine default constructed"<<endl;
}
Gold_Mine::Gold_Mine( int inputId, Cart_Point inputLoc):Game_Object('G',inputId,inputLoc)
{
	state = 'f'; //full
	amount = 100;
	cout<<"Gold_Mine constructed"<<endl;
}
bool Gold_Mine::is_empty( )
{
	return ( amount==0 );
}
double Gold_Mine::dig_gold( double amount_to_dig )
{
	if (amount>=amount_to_dig)
	{
		amount-=amount_to_dig;
		return amount_to_dig;
	}else
	{
		amount_to_dig=amount;
		amount=0;
		return  amount_to_dig;
	}
}
bool Gold_Mine::update( )
{
	if (is_empty( ) )
		if(state =='f')
		{
			state = 'e'; //sets state empty
			display_code = 'g';
			cout<<"Gold_Mine "<<get_id()<<" has been depleted."<<endl;
			return true;
		}
		return false;
}
void Gold_Mine::show_status( )
{
	cout<<"Gold_Mine status:";
	Game_Object::show_status();
	cout<<"    Contains "<<amount<<endl;
}
Gold_Mine::~Gold_Mine()
{
	cout<<"Gold_Mine destructed."<<endl;
}
double Gold_Mine::get_gold_amount()
{
	return amount;
}
void Gold_Mine::save(ofstream & file )
{
	Game_Object::save(file);
	file<<amount<<' ';
}
void Gold_Mine::restore(ifstream &file, Model &model )
{
	Game_Object::restore(file,model);
	file>>amount;
}