// this is just some debugging and pokearound without having to go to AVR (quicker for debugging 
// bitmask/flagging stuff)
//

#include "stdafx.h"
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <windows.h>


#include "program.h"

void test_command(){
	unsigned __int16 command;
	
	command = 0x00;	

	// lets set up a basic program
	command &= ~(0<<CMD_DIR);	// move forwards (clear bit PGM_DIR)
	command |=  (1<<CMD_SPD01);	
	command |=  (1<<CMD_SPD00);	// sets to 1/8th speed.
	command &= ~(0<<CMD_FLIP);	// make sure the pattern is regular 

	command += 4095;	// you can only have a max of 4095 ticks
					

	printf("ticks: %u\n",CMD_GET_TICK(command));
	printf("speed: %u\n",CMD_GET_SPEED(command));
	printf("flip: %u\n",CMD_GET_FLIP(command));
	printf("dir: %u\n",CMD_GET_DIR(command));
	}


int _tmain(int argc, _TCHAR* argv[])
{

	test_command();


	return 0;
}