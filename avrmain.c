/* port assignments */
/* PORTC is our core O set (allows us to send a wave of data)
   C0-C3 : output pints
   high/low/high/low chnA/B
   C0 - A Low
   C1 - A High
   C2 - B low
   C3 - B high
   0x0000HLHL
   0x0000BBAA
   A == low two bits
   B == next two bits
      
   PORTD : core input
   D3 : major trip switch
   D4 : return home trip switch
   
   what's left:
   
   C4,C5
   D5,D6,D7
   B0,B1,B2
   
    Does flagging INT0 as high mean we'll always break?

   */
   
   


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



#define MAGIC_OCRA_COUNT 38
#define MAGIC_TICK_COUNT 100

    
#define STATE_DEEP_SLEEP 3
#define STATE_NORMAL_SLEEP 0
#define STATE_MOVE_OUT 1
#define STATE_MOVE_BACK 2
    
    
volatile unsigned int tick;		 // this could be a chr ifyou need 8 bit more..
volatile unsigned int watchdog; // this could be a chr ifyou need 8 bit more..
volatile unsigned char portc_state;
volatile unsigned char portb_state;
volatile unsigned char portd_state;
volatile unsigned int program_state = STATE_NORMAL_SLEEP;

// every time timer2 wakes, cpu unsleeps
ISR(TIMER2_COMPA_vect)
{
    // increment ticker and fetch all sense pins
    tick++; 
    portd_state = PIND; // read in one cycle, set the state
                        // debouncing is NOT an issue since our switches can early hold, and have no consequence
						// i lie. Debouncing is not an issue on the return switch. it is potentially an issue on the 
	// major trip switch, so some debouncing code will be necessary (basically, we will debounce all switches monitored
	// and use TCCNT0 to do so
}


ISR(TIMER0_COMPA_vect)
{
	PORTB ^=0xff;
	tick++;
}

ISR(INT0_vect){
   PORTC = 0xff;
}




ISR(PCINT2_vect){
	PORTC = 0xff;
	// PORTB = PINB^0xff;	// twiddle all bits 
	// woah. That's f'd.. i can make port b not all identical?!

	SET_IDLE();	// see macro function. This interrupt will already wake the CPU, so the first 
	// and only thing we want to do is set future sleep states to not be deep sleep

	// just a quick lazy sample that as soon as this hits, you change your SMCR to normal idle mode.
	// this is actually an acceptable wakeup solution would you believe?
	// assumes that your wakeup satte is clean.
	// PORTB &= ~(0b00000100);
}


/* system states are"
    deeper sleep
    sleeping
    
    executing program to go and switch off switch
    exeucting program to return home

    a program is a series of commands, could be variable length however, we twiddle?
   

*/
// const unsigned int command;        // base unit. command string consisting of the command and length to run
const unsigned int program[1][24]= { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} }; // extended unit, a pack of commands is 24 instructions long (arbitrary)


int main(void) {
    // -------- Inits --------- //
    DDRC |= 0b00111111; // port C is all output apart from the reset line
    PINC |= 0b01000000; // set all of port C to go LOW (excluding reset line)
    
    DDRD |= 0b00000000; // all of port D is input
    PIND |= 0b11111111; // set all of port D is set to input pullups
    
    // set up timer0 as a test system
	TCCR0A |= (1<<WGM01);	// CTC mode
	TCCR0B |= (1<<CS02) | (1<<CS00);    // div 256
	OCR0A = 2*MAGIC_OCRA_COUNT;	// let's just keep em in synch
	TIMSK0 |= (1<<OCIE0A);


    // we use Timer2 to wake up the CPU
    TCCR2B |= (1<<CS22) | (1<<CS21);    // CLK T2s div 256
                                        // CLK T2Ss is CLK IO unless you do something nuts like 
                                        // set a bit in the ASSR

    TCCR2A |= 1<<WGM21;     // set into CTC mode
    // TIMSK2 |= 1<<OCIE2A;    // set interrupt for timer2, output compare match A
    OCR2A = MAGIC_OCRA_COUNT;             // output compare match A target
                            // 40 is about 10ms, give or take, given a 1mHz system clock.
   
    ADCSRA |= (1<<ADEN);    // turn off the ADC
    PRR = 0b10000111;		// power reduction register turns off more stuff
    
    // set our sleep registers
    SET_IDLE();  // see avr_sleep.h for details. Basically, macros.
    
    
    
    // we will use port b as three output status indicators
    // B0,B1,B2
    DDRB |= 0b11111111;
    PORTB |= 0b00000101;
    
	
    // DDRB - data direction
    // PORTB - set port output state
    // PINB - read port state
    
    // set up some high level event monitoring/status regs.


    
	/* pin change interrupts */
	PCMSK2 = 0x00;	// set the mask to be empty
	PCMSK2 |= (1<<PCINT19); // set our input pints to be included in the interrupt
	PCMSK2 |= (1<<PCINT20);
	// do NOT enable this. only enable interrupts when you actually need it.



    // ------ Event loop ------ //
    PORTC = 0b00001001; // initial blinkenlights. we are alive
    sei(); // enable interrupts

    
    // PORTB = 0xff;	// twiddle all bits 
    while (1) {
        
        // just something quick to report on portD
        // mapping pins D4, D3 to B1,B0
         // PORTB = ((portd_state >> 3) & 0b00000011);

            
        
        // this code will always be executed post interrupt.
        // this is the basic state switching logic, and operates at the speed of the timer

        switch(program_state){
            case STATE_NORMAL_SLEEP:
                if (portd_state & MAJOR_TRIP_MASK){        
                    program_state = STATE_MOVE_OUT;
                    // entry into a new state. should have the state init here.
                    // set movement to be zero
                    }
                // watchdog condition would go here
                break;
                
            case STATE_MOVE_OUT:
                if (!(portd_state & MAJOR_TRIP_MASK)){    // test for the major trip being set to zero
                    program_state = STATE_MOVE_BACK;
                    }
                /*
                else if (portd_state & RETURN_TRIP_MASK) {   // we always allow for the trip switch to trip
                    program_state = STATE_NORMAL_SLEEP;
                    }*/
                break;
                
            case STATE_MOVE_BACK:
                if (portd_state & MAJOR_TRIP_MASK){    // test for the major trip being set to zero
                    program_state = STATE_MOVE_OUT;
                    }
                else if (portd_state & RETURN_TRIP_MASK) {   // we always allow for the trip switch
                    program_state = STATE_NORMAL_SLEEP;
                    }
                break;
                
            default:    // some kind of emergency fallthrough?
                break;
            }


         if (tick >MAGIC_TICK_COUNT){
            // do stuffs
			// PCICR |= (1<<PCIE2);	// set the relevant PCI reg to go high, enable pinchange interrupts
			// SET_POWER_DOWN();	// go to sleep mode
            PORTC ^= 0b00001111;    // toggle low four.
			// PORTB |= 0b00000100;
            tick = 0;   // reset action counter.
            }
        sleep_cpu();
		// all these figures include the value of the LEDs being held high.
		
        // 0.7 mA diff between sleep/idle and non sleep 
        // 23.0 mA in power-save
        // 23.2 mA in idle
        // 21.1 ma in power down.  <-- needs int0 wakeup
        }
    return (0); 
    }

/* need to build an LED probe board. 

   Basically, takes it's own independent power rail set and can be hair triggered with 3v3 or greater 
   
   Would make life easier for stat monitoring.. and use up some of the junk i've accumulated *ahem*
   */