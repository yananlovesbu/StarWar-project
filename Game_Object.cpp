#include <iostream>
#include "Game_Object.h"
#include "Model.h"
using namespace std;
Game_Object::Game_Object( ):location()
{
	display_code=' ';
	state = 's';
	id_num = 0;
	cout<<"Game_Object default constructed."<<endl;
}
Game_Object::Game_Object(char in_code):location()
{
	display_code=in_code;
	state = 's';
	id_num = 0;
	cout<<"Game_Object constructed."<<endl;
}
Game_Object::Game_Object(char in_code, int in_id, Cart_Point in_loc):location(in_loc.x,in_loc.y)
{
	display_code=in_code;
	state = 's';
	id_num = in_id;
	cout<<"Game_Object constructed."<<endl;
}
Cart_Point Game_Object::get_location()
{
	return location;
}
int Game_Object::get_id()
{
	return id_num;
}
void Game_Object::show_status()
{
	cout<<display_code<<id_num
		<<" at "<<location<<' ';
}
void Game_Object::drawself(char * ptr)
{
	*ptr=display_code;
	*(ptr+1)='0'+id_num;
}
Game_Object::~Game_Object()
{
	cout<<"Game_Object destructed."<<endl;
}
bool Game_Object::is_alive()
{
	return true;
}
void Game_Object::save(ofstream & file )
{
	file<<display_code<<' '<<id_num<<' '
		<<location.x<<' '<<location.y<<' '<<state<<' ';
}
void Game_Object::restore(ifstream &file, Model &model )
{
	file>>display_code>>id_num>>location.x>>location.y>>state;
}
char Game_Object::get_display_code()
{
	return display_code;
}