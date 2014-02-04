#include "Person.h"
#include "Model.h"
#include "Inspector.h"

Inspector::Inspector( ):Person('I'),origin()
{
	name="Tom";
	cout<<"Inspector default constructor."<<endl;
}
Inspector::Inspector(int in_id,Cart_Point in_loc,const char * in_name):Person('I',in_id,in_loc),origin()
{
	name=in_name;
	cout<<"Inspector constructor."<<endl;
}
Inspector::Inspector( int in_id,Cart_Point in_loc):Person('I',in_id,in_loc),origin()
{
	name="Tom";
	cout<<"Inspector constructor."<<endl;
}
Inspector::~Inspector( )
{
	cout<<"Inspector destructor."<<endl;
}
void Inspector::show_status()
{
	cout<<"Inspector status:";
	Person::show_status();
	switch (state)
	{
	case 'o':	cout<<"  Outbound Inspecting.";
		break;
	case 'g':	cout<<"  Doing outbound inspection.";
		break;
	case 'i':		cout<<"  Inbound Inspecting.";
		break;
	case 'd':	cout<<"  Doing inbound inspection. ";
		break;
	default:		break;
	}//end switch
	cout<<endl;

}
bool Inspector::update( )
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
	case 'o':	//outbound to the closest mine
		{
			//show_status();
			if ( update_location() )
			{
				state='g';
				return true;
			}
			break;
		} 
	case 'g':	//output the mine info
		{
			//show_status();
			cout<<display_code<<get_id()<<": This Mine "<<(mine_inspected.back() )->get_display_code()<<(mine_inspected.back() )->get_id()
				<< " contains "<<mine_amounts.back()<<" of gold"<<endl;
			if (mine_uninspected.empty())
			{
				cout<<"heading back."<<endl;
				mine_amounts.pop_back();
				mine_inspected.pop_back();
				setup_destination( ( mine_inspected.back() )->get_location() );
				state='i';
				return true;
			}
			else
			{
				double mindist=100.0;//as the gird max coordinates is (20 20)
				list<Gold_Mine *>::iterator minIter;
				//find the closest gold_mine
				for (list<Gold_Mine *>::iterator beg=mine_uninspected.begin();beg!=mine_uninspected.end();beg++)
					if(  cart_distance( location, (*beg)->get_location() )<mindist )
					{
						mindist=cart_distance( location, (*beg)->get_location() );
						minIter=beg;
					}
				mine_inspected.push_back(*minIter);
				mine_amounts.push_back((*minIter)->get_gold_amount() );
				setup_destination((*minIter)->get_location() );
				mine_uninspected.erase(minIter);
				state='o';
			}
			//return true;
			break;
		} 
	case 'i':		//inbound inspecting
		{
			//show_status();
			if( update_location( ) )
			{
				state ='d';
				return true;
			}
			break;
		}
	case 'd':		//arrived to a inspected mine
		{
			if (! (mine_inspected.empty() ) )
			{
				cout<<display_code<<get_id()<<": Amount of gold removed from mine "<<( mine_inspected.back() )->get_display_code()
					<<( mine_inspected.back() )->get_id()<<" is "
					<<( mine_amounts.back()-( mine_inspected.back() )->get_gold_amount() )<<endl;
				mine_inspected.pop_back();
				mine_amounts.pop_back();
				if (! (mine_inspected.empty() ) )
					setup_destination( ( mine_inspected.back() )->get_location() );
				else
					setup_destination(origin);
				state='i';
				return false;
			}
			else
			{
				cout<<"inspection trip completed."<<endl;
				state ='s';
				return true;
			}
			//return true;
		}
	case 'x': break;
	default: break;
	}//end switch
	return false;

}
void Inspector::start_inspecting( Model & model)
{
	if(state=='x')
	{
		cout<<"I'm dead, I can't inspect !!!!"<<endl;
		return;
	}
	if ( (state!='s')||  (!mine_amounts.empty() ) || ( !mine_inspected.empty() )  || (!mine_uninspected.empty() ) )
	{
		cout<<"I'm inspecting ,but i'll start a new inspection!"<<endl;
		mine_amounts.clear();
		mine_inspected.clear();
		mine_uninspected.clear();
	}
	//if a inspector told to start inspect again,all memory previous should removed 
	
	cout<<display_code<<get_id()<<": Starting inspection trip."<<endl;
	origin=location;
	mine_uninspected=model.get_Gold_Mine_list();
	double mindist=100.0;//as the gird max coordinates is (20 20)
	list<Gold_Mine *>::iterator minIter;
	//find the closest gold_mine
	for (list<Gold_Mine *>::iterator beg=mine_uninspected.begin();beg!=mine_uninspected.end();beg++)
	{
		if(  cart_distance( location, (*beg)->get_location() )<mindist )
		{
			mindist=cart_distance( location, (*beg)->get_location() );
			minIter=beg;
		}
	}
	mine_inspected.push_back(*minIter);
	mine_amounts.push_back((*minIter)->get_gold_amount() );
	setup_destination((*minIter)->get_location() );
	mine_uninspected.erase(minIter);
	state='o';//outbound
}
void Inspector::save(ofstream & file )
{
	Person::save(file);
	file<<name<<' '<<origin.x<<' '<<origin.y<<' ';
	file<<mine_amounts.size()<<' ';
	if (mine_amounts.size()>0)
		for(list<double>::iterator beg=mine_amounts.begin();beg!=mine_amounts.end();beg++)
			file<<(*beg)<<' ';
	file<<mine_inspected.size()<<' ';
	if ( mine_inspected.size()>0 )
		for(list<Gold_Mine*>::iterator beg=mine_inspected.begin();beg!=mine_inspected.end();beg++)
			file<<( (*beg)->get_id() )<<' ';
	file<<mine_uninspected.size()<<' ';
	if( mine_uninspected.size()>0)
		for(list<Gold_Mine*>::iterator beg=mine_uninspected.begin();beg!=mine_uninspected.end();beg++)
			file<<(*beg)->get_id()<<' ';
}
void Inspector::restore(ifstream &file, Model &model )
{
	Person::restore(file,model);
	file>>name>>origin.x>>origin.y;
	int size,ID;
	double tmp;
	file>>size;
	if (size>0)
	{
		for(int i=0;i<size;i++)
		{
			file>>tmp;
			mine_amounts.push_back(tmp);
		}
	}
	file>>size;
	if (size>0)
	{
		for(int i=0;i<size;i++)
		{
			file>>ID;
			mine_inspected.push_back(model.get_Gold_Mine_ptr(ID));
		}
	}
	file>>size;
	if (size>0)
	{
		for(int i=0;i<size;i++)
		{
			file>>ID;
			mine_uninspected.push_back(model.get_Gold_Mine_ptr(ID));
		}
	}
}