#ifndef _INPUT_HANDLING_H
#define  _INPUT_HANDLING_H

class Invalid_Input
{
public:
	Invalid_Input(char * in_ptr):msg_ptr(in_ptr){ }
	 const char* const msg_ptr;
private:
	Invalid_Input( );
};
#endif