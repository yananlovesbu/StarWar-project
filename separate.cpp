#include <fstream>
#include "separate.h"
#include "Person.h"
#include "Input_Handling.h"
using namespace std;
void do_move_command(Model &model)
{
	int ID;
	double x,y;
	Person *ptrP=NULL;
	if(!(cin>>ID>>x>>y) )//check the input error
		throw Invalid_Input( "move command digit input error!" );
	if ( ( ptrP=model.get_Person_ptr(ID) ) )
		ptrP->start_moving( Cart_Point(x,y) );
	else
		throw Invalid_Input( "incorrect Miner id in move command!" );
}
void do_work_command(Model &model)
{
	int minerID,gmID,thID;
	Person *pP=NULL;
	Gold_Mine *pG=NULL;
	Town_Hall *pT=NULL;
	if(!(cin>>minerID>>gmID>>thID) )
		throw Invalid_Input( "work command ID input error!" );
	if( (pP=model.get_Person_ptr(minerID) ) && ( pG=model.get_Gold_Mine_ptr(gmID) ) && ( pT=model.get_Town_Hall_ptr(thID) ) )
		pP->start_mining(pG,pT);
	else
		throw Invalid_Input( "incorrect ID in work command!" );
}
void do_stop_command(Model &model)
{
	int minerID;
	Person *pP=NULL;
	if( !(cin>>minerID) )
		throw Invalid_Input( "stop command ID input error!" ) ;
	if ( ( pP=model.get_Person_ptr(minerID)))
		pP->stop();
	else
		throw Invalid_Input( "incorrect Miner id in stop command!" );
}
void do_go_command(Model &model)
{
	cout<<"Advancing one tick"<<endl;
	model.update();
}
void do_run_command(Model &model)
{
	int i=0;
	cout<<"advancing to next event."<<endl;
	while(i<5)
	{
		i++;
		if (model.update())
			break;
	}
}

void do_list_command( Model &model)
{
	model.show_status();
}
void do_attack_command(Model&Model)
{
	int pID1,pID2;
	Person *pP1=NULL,*pP2=NULL;
	if ( !(cin>>pID1>>pID2) )
		throw Invalid_Input( "attack command ID input error!" );
	pP1=Model.get_Person_ptr(pID1);
	pP2=Model.get_Person_ptr(pID2);
	if (pP1&&pP2)
		pP1->start_attack(pP2);
	else
		throw Invalid_Input( "incorrect Person id in attack command!" );
}
void do_new_command(Model & model)
{
	char type;
	int ID;
	double x,y;
	if (! ( cin>>type>>ID>>x>>y ))
		throw Invalid_Input( "new command digits input error!" );
	model.handle_new_command(type,ID,Cart_Point(x,y) );
}
void do_inspect_command(Model& model)
{
	int ID;
	if ( !(cin>>ID) )
		throw Invalid_Input( "inspect command ID input error!" );
	Person *pP=model.get_Person_ptr(ID);
	if (pP)
	{
		if (! ( ( model.get_Gold_Mine_list() ).empty() ) )
			pP->start_inspecting(model); //
	}
	else
		throw Invalid_Input( "incorrect Person id in inspect command!" );
}
void do_save_command(Model &model)
{
	char filename[100]={0};
	cin>>filename;
	ofstream ofs;
	ofs.open(filename,ios::out);
	model.save(ofs);
	cout<<"save "<<filename<<" complete!"<<endl;
	ofs.close();
}
void do_restore_command(Model & model)
{
	char filename[100]={0};
	cin>>filename;
	ifstream ifs;
	ifs.open(filename,ios::in ) ;
	if(ifs)
		model.restore(ifs);
	else
		throw Invalid_Input("open file failure in restore command!");
	ifs.close();
	cout<<"restore complete!"<<endl;
	
}