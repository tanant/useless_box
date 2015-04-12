#ifndef PINDEFS_H
#define PINDEFS_H

/* pindefs.h */

/* pin definitions and port assignments
  

   PORTC is our core output set (allows us to send a wave of data)
  
   C0-C3 : output pints
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
   
   PORTB - some basic sense registers
   B0,B1,B2
   
   what's left:
   C4,C5
   D5,D6,D7
   
   
    Does flagging INT0 as high mean we'll always break?

   */
   
   
#define SWITCH_MAJOR_TRIP 3
#define SWITCH_RETURN_TRIP 4

#define MAJOR_TRIP_MASK  0x08
#define RETURN_TRIP_MASK 0x10

#endif