#include <iostream>
#include <cmath>
#include "Person.h"
#include "Miner.h"
#include "Model.h"

using namespace std;

Miner::Miner( ):Person('M')
{
	display_code = 'M';
	amount = 0.0;
	mine = NULL;
	home = NULL;
	cout << "Miner default constructed"<<endl;
}
Miner::Miner( int in_id, Cart_Point in_Loc):Person('M',in_id,in_Loc)
{
	amount = 0.0;
	mine = NULL;
	home = NULL;
	cout << "Miner constructed"<<endl;
}

bool Miner::update( )
{
	switch(state)
	{
	case 's':		//state stopped
		{
			//show_status( );
			break;
		}	
	case 'm':	//state moving
		{
			//show_status();
			if( update_location( ) )
			{
				state='s';
				return true;
			}
			break;
		}
	case 'o':	//outbound mining
		{
			//show_status();
			if ( update_location() )
			{
				state='g';
				return true;
			}
			break;
		} 
	case 'g':	//getting gold
		{
			//show_status();
			amount=mine->dig_gold( );
			cout<<display_code<<get_id( )<<": Got "<<amount<<" gold"<<endl;
			setup_destination(home->get_location( ) );
			state='i';
			return true;
		}
	case 'i':		//inbound mining
		{
			//show_status();
			if( update_location( ) )
			{
				state ='d';
				return true;
			}
			break;
		}
	case 'd':	//depositing gold
		{
			//show_status();
			cout<<display_code<<get_id()<<": Deposit "<<amount<<" of gold."<<endl;
			home->deposit_gold(amount);
			amount=0;
			if (mine->is_empty())
			{
				state = 's';
				cout<<display_code<<get_id()<<": More work?"<<endl;
				return true;
			}else
			{
				setup_destination(mine->get_location());
				state = 'o';
				cout<<display_code<<get_id()<<": Going back for more."<<endl;
				return true;
			}
		}
	case 'x':
		{
			return false;
		}
	default: break;
	}//end switch
	return false;
}
void Miner::start_mining(Gold_Mine* in_Mine, Town_Hall* in_Home)
{	
	if(state=='x')
	{
		cout<<"I'm dead, Are you kidding me? Ask a zombie to work!?!?"<<endl;
		return;
	}
	mine=in_Mine;
	home=in_Home;
	setup_destination(mine->get_location());
	state='o';
	cout<<"Miner "<<get_id()<<" mining at Gold_Mine "<<mine->get_id( )
		<<" and deposit at Town_Hall "<<home->get_id()<<endl;
	cout<<display_code<<get_id()<<": Yes, my lord."<<endl;
}

void Miner::show_status( )
{
	cout<<"Miner status:";
	Person::show_status();
	switch (state)
	{
	case 'o':	cout<<"  Outbound to a mine";
		break;
	case 'g':	cout<<"  Getting gold from mine.";
		break;
	case 'i':		cout<<"  Inbound to home with load: "<<amount;
		break;
	case 'd':	cout<<"  Depositing gold";
		break;
	default:		break;
	}//end switch
	cout<<endl;
}
Miner::~Miner()
{
	cout<<"Miner destructed."<<endl;
}
void Miner::save(ofstream & file )
{
	Person::save(file);
	file<<amount<<' ';
	if (home==NULL)
		file<<-1<<' ';
	else
		file<<home->get_id()<<' ';
	if (mine==NULL)
		file<<-1<<' ';
	else
		file<<mine->get_id()<<' ';
}
void Miner::restore(ifstream &file, Model &model )
{
	Person::restore( file,model );
	file>>amount;
	int id;
	file>>id;
	if (id==-1)
		home=NULL;
	else
		home=model.get_Town_Hall_ptr(id);
	file>>id;
	if (id==-1)
		mine=NULL;
	else
		mine=model.get_Gold_Mine_ptr(id);
}