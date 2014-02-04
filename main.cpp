#include <iostream>
#include "Model.h"
#include "separate.h"
#include "Input_Handling.h"
using namespace std;

int main()
{
	View view;
	Model  model;
	model.show_status();
	model.display(view);
	char command;

	while (true)
	{
		cout<<"Enter command:";
		cin>>command;
		try
		{
			switch(command)
			{
			case 'm':
				{
					do_move_command(model);
					model.display(view);
					break;
				}
			case 'w':
				{
					do_work_command(model);
					model.display(view);
					break;
				}
			case 's':
				{
					do_stop_command(model);	
					model.display(view);
					break;
				}
			case 'g':
				{
					do_go_command(model);
					model.show_status();
					model.display(view);
					break;
				}
			case  'r':
				{
					do_run_command(model);
					model.show_status();
					model.display(view);
					break;		
				}
			case 'l':
				{
					do_list_command(model);		
					break;
				}
			case 'a':
				{
					do_attack_command(model);
					model.display(view);
					break;
				}
			case 'n':
				{
					do_new_command(model);
					model.display(view);
					break;
				}
			case 'i':
				{
					do_inspect_command(model);
					model.display(view);
					break;
				}
			case 'S':
				{
					do_save_command(model);
					model.display(view);
					break;
				}
			case 'R':
				{
					do_restore_command(model);
					//model.show_status();
					model.display(view);
					break;
				}
			case 'q': 
				{
					cout<<"Terminating program"<<endl;
					return 0;
				}
			default: 
				{
					throw Invalid_Input( "ERROR:Please enter a valid command!" );
				}
			}//end switch
			cin.clear();
			cin.sync();
		}catch(Invalid_Input &excpet)
		{
			cout<<"Invalid input- "<<excpet.msg_ptr<<endl;
			cin.clear();
			cin.sync();
		}
	}//end while

	return 0;
}
