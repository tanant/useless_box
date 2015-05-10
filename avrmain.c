// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include <avr/interrupt.h>
#include <avr/power.h>    
#include <avr/sleep.h>    


// custom headers
#include "program.h"
#include "pindefs.h"
#include "avr_sleep.h"



// this is the master system frequency
#define MAGIC_OCRA_COUNT 8
#define MAGIC_TICK_COUNT 100
    

#define STATE_NORMAL_SLEEP 0
#define STATE_MOVE_OUT 1
#define STATE_MOVE_BACK 2
#define STATE_DEEP_SLEEP 3    

/**********************************/
/****** Global definitions ********/
/**********************************/
volatile unsigned int tick;
volatile unsigned char portc_state;
volatile unsigned char portb_state;
volatile unsigned char portd_state;
volatile unsigned int program_state;
volatile unsigned char portd_temp;
volatile unsigned int major_trip_count;	
volatile unsigned int return_trip_count;

volatile unsigned char cpu_state;
volatile unsigned char fish;

/**********************************/
/****** Timer definitions *********/
/**********************************/
   
#define MAJOR_TRIP_BIT 3
#define RETURN_TRIP_BIT 4

// we may ot actually need three states for this
#define MAIN_COMPLETE 3
#define MAIN_PROCESSING 1
#define MAIN_READY 0

// how many consecutive high/low bits you need to register a hit
#define SWITCH_SENSE_CYCLES 12

// Timer2 is our master heartbeat count, running continually and
// performing all housekeeping (including pin sense) work.
ISR(TIMER2_COMPA_vect){
	

	// heartbeat is only when we get an action
	

	// due to our OCRA system and the frequencies selected, we do pin sense on each interrupt
	// PIN SENSE
	portd_temp = PIND;	// grab the whole thing as one slurp

	// update our counters
	major_trip_count  = (major_trip_count<<1)  | ((portd_temp >> MAJOR_TRIP_BIT) & 0x01);
	return_trip_count = (return_trip_count<<1) | ((portd_temp >> RETURN_TRIP_BIT) & 0x01);
	
	// determine if you update the port state
    if ((major_trip_count & (~(0xff<<SWITCH_SENSE_CYCLES))) == 0)
		{
		portd_state = portd_state & (~(1<<MAJOR_TRIP_BIT));	// clear the bit, preserve the rest
		}
	else{
		if ((major_trip_count & (~(0xff<<SWITCH_SENSE_CYCLES))) == (~(0xff<<SWITCH_SENSE_CYCLES)) ) {
			portd_state = portd_state | (1<<MAJOR_TRIP_BIT);	// set the bit
			}
		}

    if ((return_trip_count & (~(0xff<<SWITCH_SENSE_CYCLES))) == 0) {
		portd_state = portd_state & (~(1<<RETURN_TRIP_BIT));	// clear the bit, preserve the rest
		}
	else{
		if ((return_trip_count & (~(0xff<<SWITCH_SENSE_CYCLES))) == (~(0xff<<SWITCH_SENSE_CYCLES)) ) {
			portd_state = portd_state | (1<<RETURN_TRIP_BIT);	// set the bit
			}
		}
	

	


	// if the cpu has marked its run as complete, do housekeeping where we 
	//  - toggle the hearbeat pin (to keep a check on the freq of operation)
	//  - flip a bit
	if (cpu_state == MAIN_COMPLETE){

		tick = 1;	// reset and tick once
		cpu_state = MAIN_READY;	// allow CPU to do stuff again
		}
	else{
		tick++;	// increment the heartbeat ticker.
		}
}

// Timer0 is not used. 
ISR(TIMER0_COMPA_vect){
}

// PCINT2 is an odd duck, it should do no work, all it does is kick 
// the CPU back into a live state. Since pin state sense is done in TIMER2
// there is no penalty for spurious wakeup aside from battery life.
// there should also be no work done here!
ISR(PCINT2_vect){
}


int main(void) {

	// -------- Init pins --------- //
    DDRC |= 0b00111111; // port C is all output apart from the reset line
    PINC |= 0b01000000; // set all of port C to go LOW (excluding reset line)
    
    DDRD |= 0b00000000; // all of port D is input
    PIND |= 0b11111111; // set all of port D is set to input pullups
    

	
	// -------- Init Timers and interrupts --------- //
    
	// -------- TIMER2 --------- //
    TCCR2B |= (1<<CS22) | (1<<CS21);    // CLK T2s div 256
                                        // CLK T2Ss is CLK IO unless you do something nuts like 
                                        // set a bit in the ASSR
    TCCR2A |= 1<<WGM21;			        // set into CTC mode
    TIMSK2 |= 1<<OCIE2A;				// set interrupt for timer2, output compare match A
    OCR2A = MAGIC_OCRA_COUNT;           // how many ticks between this function firing/wakeup. It's basically a timer resolution.

	// using the internal 8MHz oscillator, divided by 8 gives us a master 1MHz clock
	// divide by 256 is something like 3906Hz which is kinda stupid fast.
	// some rough guess numbers: let's use an OCRA of 8 which is a max freq 488hz, which means switch holds get to check for 10 cycles == 1/48th second
	// the problem is we have such a wildly different frequency between scanning pins, and acting on the program.
	
	    
	// -------- PIN CHANGE 2 --------- //
	PCMSK2 = 0x00;	// set the mask to be empty
	PCMSK2 |= (1<<PCINT19); // set our input pints to be included in the interrupt
	PCMSK2 |= (1<<PCINT20);
	// PCICR |= (1<<PCIE2);	// this will enable PCI2, don't do it til you need it.
	

    



    // we will use port b as three output status indicators
    // B0,B1,B2
    DDRB |= 0b11111111;

    
	PORTC = 0x05;	// 00000101
	



    // ------ Event loop ------ //

    sei(); // enable interrupts

	
	program_state = STATE_NORMAL_SLEEP;
    PORT_STATUS |= 0x01;	
	
	

#define STATUS00 {PORTB &= ~((1<<STATUS_MODE0) | (1<<STATUS_MODE1));}
#define STATUS01 {PORTB &= ~((1<<STATUS_MODE0) | (1<<STATUS_MODE1)); PORTB |= 1<<STATUS_MODE0;}
#define STATUS10 {PORTB &= ~((1<<STATUS_MODE0) | (1<<STATUS_MODE1)); PORTB |= 1<<STATUS_MODE1;}
#define STATUS11 {PORTB &= ~((1<<STATUS_MODE0) | (1<<STATUS_MODE1)); PORTB |= 1<<STATUS_MODE1; PORTB |= 1<<STATUS_MODE0;}

    while (1) {
		// state management logic
		// we check for sleep state changes constantly rather than on-tick because switch triggers can affect this
		// and they're async-ish (not aligned on tick)
		switch(program_state){
			case STATE_NORMAL_SLEEP:
				STATUS11;

				// rules with masks:
				// if port & MASK == 0 bit is not set  (i.e. switch CLOSED)
				// if port & MASK != 0 bit is set (i.e. switch OPEN)


				if ((portd_state & MAJOR_TRIP_MASK) == 0){
					program_state = STATE_MOVE_OUT;
					// entry into a new state. should have the state init here.
					// set movement to be zero
					}
				// watchdog condition would go here
				break;
                
			case STATE_MOVE_OUT:	// moving to try turn itself off
				STATUS10;
				// test for the major trip being set to zero, which means we have flicked it and we can now move back
				// we do not allow/care for the case of the return trip to be triggered.
				if ((portd_state & MAJOR_TRIP_MASK) != 0){    
					program_state = STATE_MOVE_BACK;
					}
				break;
                
			case STATE_MOVE_BACK:
				STATUS01;

				if ( (portd_state & RETURN_TRIP_MASK) == 0 ) {   // this is our 'we have returned' condition
					program_state = STATE_NORMAL_SLEEP;
					}

				if ((portd_state & MAJOR_TRIP_MASK) ==0){		// someone has hit the switch again.

					program_state = STATE_MOVE_OUT;
					}

				break;
                
			default:    // some kind of emergency fallthrough?
				break;
			}






		// if ((tick >= MAGIC_TICK_COUNT)&&(cpu_state == 0) )
		// for some crazy freaking reason, the above statement glitches, while the lower statement does not
		// I'd like to blame optimsation and interrupts but I dunno..

		if ((cpu_state == MAIN_READY)&&(tick >= MAGIC_TICK_COUNT) ) {		// entrant if we are not in the middle of a processing loop
			// do work
			PORT_STATUS ^= (1<<HEARTBEAT_PIN);


			// work done
			
			cpu_state = MAIN_COMPLETE;										// indicate the cpu has marked the tick as dirty but all work completed.
			// because this loop is only interruptible, we will never test for MAIN_READY until we reach the end
			// so we can last with a simple two-state system, once you're in the loop, you're implicitly working.
			}		
		sleep_cpu();			// for good form, go sleep.
        }
    return (0); 
    }
