#include "Person.h"
#include "Soldier.h"
#include "Model.h"

Soldier::Soldier():Person('S')
{
	attack_strenth=2;
	range=2.0;
	target=NULL;
	cout<<"Soldier default constructor"<<endl;
}

Soldier::Soldier(int in_id, Cart_Point in_loc ):Person('S',in_id,in_loc)
{
	attack_strenth=2;
	range=2.0;
	target=NULL;
	cout<<"Soldier constructor"<<endl;
}
void Soldier::start_attack(Person* in_target)
{
	if(state=='x')
	{
		cout<<"I'm dead, you do not have the ability to summon the undead."<<endl;
		return;
	}
	if (cart_distance(location,in_target->get_location())<=range)
	{
		cout<<display_code<<get_id()<<": Attacking!"<<endl;
		target=in_target;
		state='a';
	}
	else
		cout<<"Target is out of range"<<endl;
}
bool Soldier::update()
{
	switch (state)
	{
	case 'x':
		return false;
	case 's':
		return false;
	case 'm':
		{
			//show_status();
			if( update_location( ) )
			{
				state='s';
				return true;
			}
			break;
		}
	case 'a':
		{
			if (cart_distance(location,target->get_location())<=range)
			{
				if (target->is_alive())
				{
					cout<<display_code<<get_id()<<": Take That!"<<endl;
					target->take_hit(attack_strenth,this);
					return false;
				}
				else
				{
					cout<<display_code<<get_id()<<": I win!"<<endl;
					state='s';
					return true;
				}
			}//end if
			else
			{
				cout<<"Target is out of range"<<endl;
				state='s';
				return true;
			}//end else
		}//end case
	default:
		break;
	}//end switch
	return false;
}
void Soldier::show_status()
{
	cout<<"Soldier status:";
	Person::show_status();
	if (state=='a')
	{
		cout<<" attacking!";
	}
	cout<<endl;
}
Soldier::~Soldier()
{
	cout<<"Soldier destructed. "<<endl;
}
void Soldier::save(ofstream & file )
{
	Person::save(file);
	file<<attack_strenth<<' '<<range<<' ';
	if(target==NULL)
		file<<-1<<' ';
	else
		file<<target->get_id()<<' ';
}
void Soldier::restore(ifstream &file, Model &model )
{
	Person::restore(file,model);
	file>>attack_strenth>>range;
	int ID;
	file>>ID;
	if(ID==-1)
		target=NULL;
	else
		target=model.get_Person_ptr(ID);
}
void Soldier::take_hit(int attack_strenth,Person * attack_ptr )
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
		if (health<3 && 'A'<=display_code && 'Z'>=display_code)	
			display_code+=('a'-'A');
		start_attack(attack_ptr);
	}
}