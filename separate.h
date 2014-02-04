#ifndef	_SEPARATE_H
#define	_SEPARATE_H

#include "Model.h"

void do_move_command(Model &model);
void do_work_command(Model &model);
void do_stop_command(Model &model);
void do_go_command(Model &model );
void do_run_command(Model &model );
void do_list_command( Model &model);
void do_attack_command(Model&Model);
void do_new_command(Model& model);
void do_inspect_command(Model& model);
void do_save_command(Model &model);
void do_restore_command(Model & model);

#endif