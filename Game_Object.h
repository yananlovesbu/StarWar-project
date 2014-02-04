#ifndef _GAME_OBJECT_H
#define  _GAME_OBJECT_H
#include <fstream>
#include "Cart_Point.h"
class Model;
class Game_Object 
{
public:
	Game_Object();
	Game_Object(char in_code);
	Game_Object(char in_code, int in_id, Cart_Point in_loc);
	Cart_Point get_location( );
	int get_id( );
	virtual void show_status( );
	void drawself( char * ptr);
	virtual ~Game_Object();
	virtual bool is_alive( );
	virtual bool update( )=0;
	virtual void save(ofstream & file );
	virtual void restore(ifstream &file, Model &model );
	char get_display_code();
protected:
	Cart_Point location;
	char display_code;
	char state;
private:
	int id_num;
};

#endif