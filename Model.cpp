#include "Person.h"
#include "Miner.h"
#include "Soldier.h"
#include "Inspector.h"

#include "Model.h"


Model::Model()
{
	time=0;
	person_ptrs.push_back( new Miner( 1,Cart_Point(5,1) ) );
	object_ptrs.push_back( person_ptrs.back() );
	person_ptrs.push_back(new Miner( 2,Cart_Point(10,1) ) );
	object_ptrs.push_back( person_ptrs.back() );
	person_ptrs.push_back( new Soldier(3,Cart_Point( 5,15 ) ) );
	object_ptrs.push_back(person_ptrs.back() );
	person_ptrs.push_back(new Soldier(4,Cart_Point( 10,15) ) );
	object_ptrs.push_back(person_ptrs.back());
	person_ptrs.push_back(new Inspector(5,Cart_Point( 5,5),"Clouseau" ) );
	object_ptrs.push_back(person_ptrs.back());
	mine_ptrs.push_back(new Gold_Mine(1,Cart_Point(1,20)) );
	object_ptrs.push_back(mine_ptrs.back() );
	mine_ptrs.push_back( new Gold_Mine(2,Cart_Point(10,20)) );
	object_ptrs.push_back( mine_ptrs.back() );
	hall_ptrs.push_back(new Town_Hall( ) );
	object_ptrs.push_back( hall_ptrs.back() );
	
	active_ptrs=object_ptrs;//all the obj is alive at first

	cout<<"Model default constructed"<<endl;
}
Model::Model(Model &)
{

}
Model::~Model()
{
	for (list<Game_Object*>::iterator beg=object_ptrs.begin();beg!=object_ptrs.end();beg++)
		delete (*beg);
	object_ptrs.clear();
	active_ptrs.clear();
	hall_ptrs.clear();
	mine_ptrs.clear();
	cout<<"Model destructed."<<endl;
}
Person* Model::get_Person_ptr(int id)
{
	for (list<Person*>::iterator beg=person_ptrs.begin();beg!=person_ptrs.end();beg++)
		if ( (*beg)->get_id()==id)
		{
			return *beg;
		}
	return NULL;
}
Gold_Mine*  Model::get_Gold_Mine_ptr(int id)
{
	for(list<Gold_Mine*>::iterator beg=mine_ptrs.begin();beg!=mine_ptrs.end();beg++)
		if ( (*beg)->get_id()==id)
		{
			return *beg;
		}
	return NULL;
}
Town_Hall* Model::get_Town_Hall_ptr(int id)
{
	for (list<Town_Hall*>::iterator beg=hall_ptrs.begin();beg!=hall_ptrs.end();beg++)
		if ( (*beg)->get_id()==id)
		{
			return *beg;
		}
	return NULL;
}
bool Model::update()
{
	bool flag=false;
	int i=0;
	time++;
	for(list<Game_Object*>::iterator beg=active_ptrs.begin();beg!=active_ptrs.end();beg++,i++)
		if( (flag |=(*beg)->update()) )
			break;
	for(list<Game_Object*>::iterator beg=active_ptrs.begin();beg!=active_ptrs.end();)
	{
		if (!( (*beg)->is_alive() ) )
		{
			beg=active_ptrs.erase(beg);//the erase member may leads beg invalid
			cout<<"Dead object removed."<<endl;
		}else
			beg++;
	}
	return flag;
}
void Model::display(View &view)
{
	view.clear();
	for(list<Game_Object*>::iterator beg=active_ptrs.begin();beg!=active_ptrs.end();beg++)
			view.plot( *beg );
	view.draw();
}
void Model::show_status()
{
	cout<<"Time: "<<time<<endl;
	for(list<Game_Object*>::iterator beg=object_ptrs.begin();beg!=object_ptrs.end();beg++)
		(*beg)->show_status();
}
void Model::handle_new_command(char type, int in_id,Cart_Point in_loc )
{
	if (in_id<0 || in_id>9)
		throw Invalid_Input( "in new command: the id should be 0-9!" );
	if ( (in_loc.x<0) || (in_loc.x>20) || (in_loc.y<0) || (in_loc.y>20) ) //as the grid's max coordinates is (20,20)
		throw Invalid_Input("in new command: the x and y should both be 0-20!" );
	switch (type)
	{
	case 'G':
	case 'g':
		{
			if (get_Gold_Mine_ptr(in_id))
				throw Invalid_Input("in new command: input a duplicated Gold_Mine ID ");
			mine_ptrs.push_back( new Gold_Mine (in_id,in_loc) );  
			object_ptrs.push_back(mine_ptrs.back() );
			active_ptrs.push_back(mine_ptrs.back() );
			break;
		}
	case 'T':
	case 't':
		{
			if (get_Town_Hall_ptr(in_id))
				throw Invalid_Input("in new command: input a duplicated Town_Hall ID ");
			hall_ptrs.push_back( new Town_Hall (in_id,in_loc) );  
			object_ptrs.push_back(hall_ptrs.back() );
			active_ptrs.push_back(hall_ptrs.back() );
			break;
		}
	case 'M':
	case 'm':
		{
			if (get_Person_ptr(in_id))//the soldier and miner are all stored in person_ptrs,their id can not be duplicated
				throw Invalid_Input("in new command: input a duplicated Person ID ");
			person_ptrs.push_back( new Miner (in_id,in_loc) );  
			object_ptrs.push_back(person_ptrs.back() );
			active_ptrs.push_back(person_ptrs.back() );
			break;
		}
	case 'S':
	case 's':
		{
			if (get_Person_ptr(in_id))
				throw Invalid_Input("in new command: input a duplicated Person ID ");
			person_ptrs.push_back( new Soldier (in_id,in_loc) );  
			object_ptrs.push_back(person_ptrs.back() );
			active_ptrs.push_back(person_ptrs.back() );
			break;
		}
	case 'I':
	case 'i':
		{
			if (get_Person_ptr(in_id))
				throw Invalid_Input("in new command: input a duplicated Person ID ");
			person_ptrs.push_back( new Inspector (in_id,in_loc) );  
			object_ptrs.push_back(person_ptrs.back() );
			active_ptrs.push_back(person_ptrs.back() );
			break;
		}
	
	default:
		throw Invalid_Input("invalid type in new command!");
	}//end switch

}
list<Gold_Mine *> Model::get_Gold_Mine_list( )
{
	return mine_ptrs;
}
void Model::save(ofstream & file )
{
	file<<time<<' ';
	file<<active_ptrs.size()<<' ';
	for(list<Game_Object*>::iterator beg=active_ptrs.begin();beg!=active_ptrs.end();beg++)
		file<<(*beg)->get_display_code()<<(*beg)->get_id()<<' ';
	file<<'\n';
	for(list<Game_Object*>::iterator beg=active_ptrs.begin();beg!=active_ptrs.end();beg++)
	{
		(*beg)->save(file);
		file<<'\n';
	}
}
void Model::restore( ifstream&file)
{
	cout<<"All objects are destroyed on DOOMS DAY!!"<<endl;
	for (list<Game_Object*>::iterator beg=object_ptrs.begin();beg!=object_ptrs.end();beg++)
		delete (*beg);
	object_ptrs.clear();
	active_ptrs.clear();
	hall_ptrs.clear();
	mine_ptrs.clear();//cleared the current state,and prepare to restore
	file>>time;
	int objnum,ID;
	char code;
	file>>objnum;
	for (int i=0;i<objnum;i++)
	{
		file>>code>>ID;
		handle_new_command(code,ID,Cart_Point(0,0) );
	}
	for (list<Game_Object*>::iterator beg=object_ptrs.begin();beg!=object_ptrs.end();beg++)
		(*beg)->restore(file,*this);

}