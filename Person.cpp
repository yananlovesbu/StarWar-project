#include <iostream>

#include "Town_Hall.h"
#include "Gold_Mine.h"
#include "Person.h"
#include "Model.h"

using namespace std;

Person::Person( ):Game_Object(),destination(),delta()
{
	speed=5.0;
	health=5;
	cout<<"Person default constructed."<<endl;
}
Person::Person( char in_code ):Game_Object(in_code),destination(),delta()
{
	speed=5.0;
	health=5;
	cout<<"Person constructed."<<endl;
}
Person::Person( char in_code, int in_id, Cart_Point in_loc ):Game_Object(in_code,in_id,in_loc),destination(),delta()
{
	speed=5.0;
	health=5;
	cout<<"Person constructed."<<endl;
}
void Person::start_moving( Cart_Point dest )
{
	if(state=='x')
	{
		cout<<"I am dead. I may move but you just cannot see me."<<endl;
		return;
	}
	setup_destination(dest);
	state = 'm'; //moving
	cout<<"Moving "<<get_id( )<<" to "<<dest<<endl;
	cout<<display_code<<get_id( )<<": On my way."<<endl;
}
void Person::stop( )
{	
	state ='s';
	cout<<"Stopping "<<get_id()<<endl;
	cout<<display_code<<get_id()<<": All right."<<endl;
}
void Person::show_status( )
{
	Game_Object::show_status();
	
	switch (state)
	{
	case 's': 
		cout<<"  Stopped ";
		break;	
	case 'x':
		cout<<"  is dead ";
		break;
	case 'm':
		cout<<"  moving at speed of "<<speed<<" towards "<<destination
			<<" at each step of "<<delta<<" ";
		break;
	default: break;
	}//end switch
}
bool Person::update_location( )
{
	if ( fabs(destination.x-location.x)<=fabs(delta.x) &&
		fabs(destination.y-location.y)<=fabs(delta.y) )//if the obj is within astep of destination
	{
		location=destination;
		cout<<display_code<<get_id()<<": I'm there!"<<endl;
		return true;
	}else
	{
		location=location+delta;
		cout<<display_code<<get_id()<<":step..."<<endl;
		return false;
	}
}
void Person::setup_destination( Cart_Point dest )
{
	dest.x=(dest.x<0.0)?0:dest.x;
	dest.y=(dest.y<0.0)?0:dest.y;
	dest.x=(dest.x>20.0)?20.0:dest.x;
	dest.y=(dest.y>20.0)?20.0:dest.y;
	destination=dest;
	delta=(destination-location)*(speed/cart_distance(destination,location));
}
Person::~Person()
{
	cout<<"Person destructed."<<endl;
}
void Person::start_mining(Gold_Mine* in_mine,Town_Hall *in_home)
{
	cout<<"Sorry,i can't work a mine."<<endl;
}
bool Person::is_alive()
{
	if (state=='x')
		return false;
	else
		return true;
}
void Person::take_hit(int attack_strenth,Person*attack_ptr)
{
	health-=attack_strenth;
	if (health<=0)
	{
		cout<<display_code<<get_id()<<": Ahh,i'm dying!"<<endl;
		//health=0;
		state ='x';
	}
	else
	{
		cout<<display_code<<get_id()<<": Ouch!"<<endl;
		cout<<display_code<<get_id()<<": I don't wanna fight!"<<endl;
		if (health<3 && 'A'<=display_code && 'Z'>=display_code)	
				display_code+=('a'-'A');
		Cart_Vector cv=location-(attack_ptr->get_location());
		cv=cv*1.5;
		start_moving( location+cv );
	}
}
void Person::start_attack(Person* target)
{
	cout<<"I can't attack."<<endl;
}
void Person::start_inspecting( Model &model)
{
	cout<<"I can't inspect."<<endl;
}
void Person::save(ofstream &file)
{
	Game_Object::save(file);
	file<<speed<<' '<<health<<' '<<delta.x<<' '<<delta.y
		<<' '<<destination.x<<' '<<destination.y<<' ';
}
void Person::restore(ifstream &file, Model &model )
{
	Game_Object::restore(file,model);
	file>>speed>>health>>delta.x>>delta.y
		>>destination.x>>destination.y;
}