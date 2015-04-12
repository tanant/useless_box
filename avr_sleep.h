/* sleep.h */
/* a way to define sleep state modifications and suchlike */


// #define PWR_IDLE (1<<SM1) | (1<<SM0)
#define PWR_IDLE 0
#define PWR_EXTSLEEP (1<<SM1) 



#define SET_POWER_DOWN() SMCR = (1<<SM1) | (1<<SE)
//#define SET_IDLE()	SMCR =  (1<<SM1) | (1<<SM0) | (1<<SE)
#define SET_IDLE()	SMCR =  0
