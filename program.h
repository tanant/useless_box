#ifndef PROGRAM_H
#define PROGRAM_H

/* program.h */
/* Functions related to managing programs/commands for the useless box 
   commands are single block commands that are composed of a 4 bit data header
   and a 12 bit length.
   
   packs into an unsigned AVR-int (a 16 bit value)
   
    bit patterns
    15    : CMD_DIR   : direction - 0 - forward, 1 - reverse
    14    : CMD_FLIP  : pattern flip
    13    : CMD_SPD01 : speed Hi
    12    : CMD_SPD00 : speed Lo
    11..0 : ticks
    
    DIR | FLIP | SPD01 | SPD00
    0 0 0 0 - forwards/full
    0 1 0 0 - forwards/zero (i.e. stop)
    0 0 0 1 - fwd half
    0 1 0 1 - fwd half (no change)   --< wasted state.
    0 0 1 0 - fwd quarter (1 in 4)
    0 1 1 0 - fwd 3/4 (3 in 4)
    0 0 1 1 - fwd eighth (1 in 8)
    0 1 1 1 - fwd 7/8 (7 in 8)
*/

#define CMD_DIR 15
#define CMD_FLIP 14
#define CMD_SPD01 13
#define CMD_SPD00 12
#define CMD_TICK_MASK 0x0fff

// Some cheeky macros for bit manipulation/replacement
#define CMD_GET_TICK(x)  (x & CMD_TICK_MASK)
#define CMD_GET_SPEED(x) ((x & (1<<CMD_SPD00 | 1<<CMD_SPD01) ) >> CMD_SPD00)
#define CMD_GET_FLIP(x)  ((x & 1<<CMD_FLIP) >> CMD_FLIP)
#define CMD_GET_DIR(x)   ((x & 1<<CMD_DIR) >> CMD_DIR)

#endif