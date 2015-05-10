// this is just some debugging and pokearound without having to go to AVR (quicker for debugging 
// bitmask/flagging stuff)
//

#include "stdafx.h"
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <windows.h>


#include "program.h"
// you get 12 commands in a program.
// that's basically f/b/f/b/f/b/f/b/f/b/s/f
// could you do programmes as a string?
// 

// using a human readable program list string - wasteful, but good.
/*
    0 0 0 0 - forwards/full
    0 1 0 0 - forwards/zero (i.e. stop)
    0 0 0 1 - fwd half
    0 1 0 1 - fwd half (no change)   --< wasted state.
    0 0 1 0 - fwd quarter (1 in 4)
    0 1 1 0 - fwd 3/4 (3 in 4)
    0 0 1 1 - fwd eighth (1 in 8)
    0 1 1 1 - fwd 7/8 (7 in 8)
	*/
// new command string, for PWM
// h - 0/8
// i - 8/8
// j - 7/8 
// k - 6/8
// l - 4/8
// m - 2/8
// n - 1/8
// note that the strings are all characters that won't be hex digits.
// each program is a . terminated string with each command being 3 chrs. 
// A command chr, then a two-chr length operator
// good practice would be to make sure the last command is always hFF or HFF so that you get 255 ticks of arm rotation
// in the direction you want. Just incase.

// these may be slightly expensive due to the cost of using 8bit chrs instead of
// literal 8 bit.
static const char *out_pgm_list = "a23b1fa00cF2...z23b12a00c22...x00c22...f81g82d92x29...";
static const char *rev_pgm_list = "a23b12a00c12...a23b12a00c22...";	

// define the max number of programs we can support in the dynamic allocation table
// this is all an expensive runtime initialisation hack, but it's better (for maint pupropses)
// than having to malloc/calloc. Mallocing on an AVR is just ASKING for trouble.
// note that if you have enough BSS then you can up this, or crunch it if you move off the ATMega328P

// also, yes, we could've made the programmer spec this and have some fun tricks involving programming
// offsets so one program might be 8 back and forths, and another would be 4, just managed via offsets.
// but that might just end up being complex.

// to be fair as well, you could just rewrite this module if you need, all this does is feed in a program tick type
// and a count. Imagine this as a fetch block.

#define PGM_LIMIT 32
#define PGM_COMMAND_SIZE 3


void initialise_pgm_list(const char *pgm_list, int *pgm_count, int pgm_offsets[]){

	// start at the beginning, and increment on 3's (#def'd earlier)
	int tmp_last_offset = 0;	// last offset is the notional start point.
	int i;	// c89 style, only init here up top

	for (i=0;i<strlen(pgm_list); i=i+PGM_COMMAND_SIZE){	
		// if you locate a dot, you've found a program endpoint. 
		if (pgm_list[i] == '.'){
			// update the offset record
			// update the program counter to indicate we've found something
			pgm_offsets[*pgm_count] = tmp_last_offset;
			(*pgm_count) =  (*pgm_count)+1;
			tmp_last_offset = i+PGM_COMMAND_SIZE;

			// safety condition, if you reach the index that'd have you doing 
			// a buffer overrun, we stop right away.
			if (*pgm_count >= PGM_LIMIT){
				break;
				}
			}
		}
		// note that this only stores programmes on a clean exit, i.e. must end with ...
		// a program string that DOESN'T end with ... and just an end of string indicator, will 
		// be picked up by this special case here
		if ( (tmp_last_offset < (strlen(pgm_list)-PGM_COMMAND_SIZE)) && (*pgm_count < PGM_LIMIT) ){
			pgm_offsets[*pgm_count] = tmp_last_offset;
			(*pgm_count)++;
			}
	}

void init(int *intptr, const char *cplist, int list[]){
	printf("intptr:%d\n",intptr);	// to feed in and modify an int pointer, we need to feed in the address of the bare int.
	printf("deref intptr:%d\n",*intptr);
	printf("const char ptr:%s\n",cplist);	// this is some kind
	printf("list[0]:%d\n",list[0]);
	}

void test_command(){
	

	// ##########################################
	// intialisation/parsing input command string 
	// ##########################################
	// these could've been static had we done them at *compile* time vs runtime
	// having said that, we have a limit on size so this is still good.
	int out_pgm_count;	
	int out_pgm_offsets[PGM_LIMIT];  // = {0};	// i think AVR will guarantee this 
	
	int rev_pgm_count;
	int rev_pgm_offsets[PGM_LIMIT];  // = {0};

	// tmp so it's clear we reuse this one
	int tmp_last_offset;
	int i;

	// dynamic program init, count and look for full stops on 3rds (off 0,3,6,9,12...)
	out_pgm_count = 0;	
	rev_pgm_count = 0;	
	initialise_pgm_list(out_pgm_list, &out_pgm_count, out_pgm_offsets);
	initialise_pgm_list(rev_pgm_list, &rev_pgm_count, rev_pgm_offsets);


	// dynamic initialization of the program.
	printf("%d\n", strlen(rev_pgm_list));
	printf("%s\n", (rev_pgm_list));

	for (i=0 ;i<rev_pgm_count;i++){
		printf("%u,", rev_pgm_offsets[i]);
		}
	printf("\n");
	for (i=0 ;i<rev_pgm_count;i++){
		printf("%c%c%c\n",rev_pgm_list[rev_pgm_offsets[i]],rev_pgm_list[rev_pgm_offsets[i]+1],rev_pgm_list[rev_pgm_offsets[i]+2]);
		}
	*/
	/*
	// lets set up a basic program

	command = 0x00;	

	command &= ~(0<<CMD_DIR);	// move forwards (clear bit PGM_DIR)
	command |=  (1<<CMD_SPD01);	
	command |=  (1<<CMD_SPD00);	// sets to 1/8th speed.
	command &= ~(0<<CMD_FLIP);	// make sure the pattern is regular 

	command += 4095;	// you can only have a max of 4095 ticks
					

	printf("ticks: %u\n",CMD_GET_TICK(command));
	printf("speed: %u\n",CMD_GET_SPEED(command));
	printf("flip: %u\n",CMD_GET_FLIP(command));
	printf("dir: %u\n",CMD_GET_DIR(command));
	*/
	}

void fn_one(int *arr){
	printf("len:%d\n",sizeof(arr));
	printf("arr[0]:%d\n",arr[0]);
	printf("arr[2]:%d\n",arr[2]);
	}

void fn_test(){
	}

int _tmain(int argc, _TCHAR* argv[])
{
	test_command();
	/*int dsa[]={1,2,3,4,5,6,7,8,9,0};
	int *dza;

	dsa[1] = 10;
	dsa[0] = 3;

	dza = malloc(sizeof(int)*10);

	

	fn_one(dsa);
	printf("si:%d\n",sizeof(dsa));

	printf("%d\n",&dsa);
	printf("%d\n",(&dsa+1));
	printf("%d\n",(&dsa+2));	// how the FECK does that work? the address of dsa, +1?
	printf("%d\n",(&dsa));	// how the FECK does that work? the address of dsa, +1?
	
	printf("------------\n");
	printf("si:%d\n",sizeof(dza));

	printf("%d\n",&dza);
	printf("%d\n",(&dza+1));
	printf("%d\n",(&dza+2));
	printf("%d\n",(&dza));	// ah, if you use malloc, then you're screwed. Gotcha.
	*/

	return 0;
}