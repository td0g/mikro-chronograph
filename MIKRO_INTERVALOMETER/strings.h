#ifndef string.h
#define strings.h
/*
 *                A
 *              F   B
 *                G
 *              E   C
 *                D
 */

#define SEG_colon 0b10000000

#define CHAR_NUMBERS {SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, SEG_B | SEG_C, SEG_A | SEG_B | SEG_D | SEG_E | SEG_G, SEG_A | SEG_B | SEG_C | SEG_D | SEG_G, SEG_B | SEG_C | SEG_F | SEG_G, SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_B | SEG_C, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G}
#define CHAR_BLANK {0}

#define TXT_ALL {SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_colon, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_colon,  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_colon,  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_colon}
#define TXT_DONE {SEG_B | SEG_C | SEG_D | SEG_E | SEG_G, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, SEG_C | SEG_E | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G}
#define TXT_GO {SEG_G,SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,SEG_G}
#define TXT_GOARMED {SEG_G | SEG_colon, SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_colon, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_colon, SEG_G | SEG_colon}
#define TXT_BRGT {SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, SEG_E | SEG_G, SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_E | SEG_F}

#define TXT_DON1 {SEG_B | SEG_C | SEG_D | SEG_E | SEG_G, SEG_C | SEG_D | SEG_E | SEG_G, SEG_C | SEG_E | SEG_G, 0}
#define TXT_DON0 {SEG_B | SEG_C | SEG_D | SEG_E | SEG_G, SEG_C | SEG_D | SEG_E | SEG_G, SEG_A | SEG_E | SEG_F | SEG_G, SEG_A | SEG_E | SEG_F | SEG_G}
#define TXT_OCAL {SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, SEG_D | SEG_E | SEG_G, SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, SEG_D | SEG_E | SEG_F}
#define TXT_TEST {SEG_A | SEG_E | SEG_F, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, SEG_A | SEG_E | SEG_F}
#define TXT_RESET {SEG_E | SEG_G, SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, SEG_A | SEG_E | SEG_F, 0}
#define TXT_OPEN {SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, SEG_A | SEG_B | SEG_E | SEG_F | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, SEG_C | SEG_E | SEG_G}
#define TXT_CLOSE {SEG_D | SEG_E | SEG_G, SEG_D | SEG_E | SEG_F, SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G}
#define TXT_INIT {SEG_B | SEG_C,                0,            SEG_A | SEG_C | SEG_D | SEG_F,            SEG_D | SEG_E | SEG_F | SEG_G,                SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,        SEG_E | SEG_G,               SEG_D | SEG_E | SEG_F | SEG_G,                0,            SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          SEG_D | SEG_E | SEG_F,                SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,        SEG_B | SEG_C | SEG_D | SEG_F | SEG_G}
#define TXT_SHOTS {SEG_B | SEG_C | SEG_F | SEG_G,            0,            SEG_D | SEG_E | SEG_G,             SEG_C | SEG_D | SEG_E | SEG_G, SEG_C | SEG_D | SEG_E,              SEG_C | SEG_E | SEG_G,              SEG_D | SEG_E | SEG_F | SEG_G,            0,                SEG_C | SEG_D | SEG_E | SEG_G,            SEG_A | SEG_E | SEG_F | SEG_G,            0,            SEG_A | SEG_C | SEG_D | SEG_F,  SEG_C | SEG_E | SEG_F | SEG_G,            SEG_C | SEG_D | SEG_E | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G,                SEG_A | SEG_C | SEG_D | SEG_F}
#define TXT_INTER {SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,          0,            SEG_A | SEG_C | SEG_D | SEG_F,                SEG_C | SEG_E | SEG_F | SEG_G,            SEG_C | SEG_D | SEG_E | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G,                SEG_G, SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,          SEG_G, SEG_A | SEG_C | SEG_D | SEG_F,            SEG_C | SEG_E | SEG_F | SEG_G,              SEG_C | SEG_D | SEG_E | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G}
//#define TXT_INTER {SEG_C | SEG_G, SEG_D, SEG_D, SEG_E | SEG_G}
#define TXT_BULB {SEG_A | SEG_B | SEG_C | SEG_D | SEG_G, 0, SEG_A | SEG_C | SEG_D | SEG_F, SEG_C | SEG_E | SEG_F | SEG_G, SEG_C | SEG_D | SEG_E, SEG_D | SEG_E | SEG_F | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, SEG_E | SEG_G, 0, SEG_C | SEG_D | SEG_E | SEG_G, SEG_A | SEG_B | SEG_E | SEG_F | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, SEG_C | SEG_E | SEG_G}
#define TXT_UP {0, SEG_C | SEG_D | SEG_E, SEG_A | SEG_B | SEG_E | SEG_F | SEG_G, 0}
#define TXT_DIR0 {SEG_B | SEG_C | SEG_D | SEG_E | SEG_G , SEG_B | SEG_C, SEG_E | SEG_G, SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F}
#define TXT_DIR1 {SEG_B | SEG_C | SEG_D | SEG_E | SEG_G , SEG_B | SEG_C, SEG_E | SEG_G, SEG_B | SEG_C}
#define TXT_OPT {0, 1, 1, 0}
#define TXT_OPT1 {0, 1, 1, 0}
#define TXT_OPT2 {2, 1, 1, 2}
#define TXT_OPTSIMON {SEG_A | SEG_C | SEG_D | SEG_F, SEG_B | SEG_C,  SEG_A |  SEG_C | SEG_E | SEG_G , SEG_C |SEG_E |SEG_G}
#define TXT_OPTTYLER {SEG_D | SEG_E | SEG_F | SEG_G,SEG_B | SEG_C | SEG_F | SEG_G,0,0}

#define TXT_ZERO {SEG_A | SEG_B | SEG_D | SEG_E | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,  SEG_E | SEG_G,  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F}
#define TXT_RECALL {SEG_E | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,  SEG_D | SEG_E | SEG_G,  SEG_D | SEG_E | SEG_F}

#define TXT_TOTALTIMELEFT {SEG_D | SEG_E | SEG_F | SEG_G, SEG_C | SEG_D | SEG_E | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, SEG_D | SEG_E | SEG_F,0, SEG_D | SEG_E | SEG_F | SEG_G, SEG_E | SEG_F, SEG_A | SEG_C | SEG_E | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, 0, SEG_D | SEG_E | SEG_F, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_E | SEG_F | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G}
#define TXT_SHOTSLEFT {SEG_A | SEG_B | SEG_E | SEG_F | SEG_G, SEG_C | SEG_E | SEG_F | SEG_G, SEG_C | SEG_D | SEG_E | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G, SEG_C | SEG_D | SEG_E | SEG_G, SEG_A | SEG_C | SEG_D | SEG_F, 0, SEG_D | SEG_E | SEG_F,  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_E | SEG_F | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G}
#define TXT_TILLNEXTSHOT {SEG_D | SEG_E | SEG_F | SEG_G, SEG_E | SEG_F, SEG_A | SEG_C | SEG_E | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, 0, SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, SEG_C | SEG_E | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G, SEG_E | SEG_F, SEG_D | SEG_E | SEG_F, 0, SEG_C | SEG_E | SEG_G, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G, SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G, 0, SEG_A | SEG_B | SEG_E | SEG_F | SEG_G, SEG_C | SEG_E | SEG_F | SEG_G, SEG_C | SEG_D | SEG_E | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G, SEG_C | SEG_D | SEG_E | SEG_G}

//Strings provided by Simon

/*Menu 1                SEG_B | SEG_C,                0,            SEG_A | SEG_C | SEG_D | SEG_F,            SEG_D | SEG_E | SEG_F | SEG_G,                SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,        SEG_E | SEG_G,               SEG_D | SEG_E | SEG_F | SEG_G,                0,            SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          SEG_D | SEG_E | SEG_F,                SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,        SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,                                                                                                                                               
1 start delay |  1n1t1al delay       SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,          0,            SEG_A | SEG_C | SEG_D | SEG_F,                SEG_C | SEG_E | SEG_F | SEG_G,            SEG_C | SEG_D | SEG_E | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G,                SEG_G, SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,          SEG_G, SEG_A | SEG_C | SEG_D | SEG_F,            SEG_C | SEG_E | SEG_F | SEG_G,              SEG_C | SEG_D | SEG_E | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G,                                                                                                                                           
2 Shot-2-shot     SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,         0,            SEG_A | SEG_C | SEG_D | SEG_F,            SEG_C | SEG_E | SEG_F | SEG_G,              SEG_C | SEG_D | SEG_E,              SEG_D | SEG_E | SEG_F | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G,               SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          SEG_E | SEG_G,               0,            SEG_C | SEG_D | SEG_E | SEG_G,               SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,          SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,                SEG_C | SEG_E | SEG_G,                                                                                                                             
3 Shutter open  SEG_B | SEG_C | SEG_F | SEG_G,            0,            SEG_D | SEG_E | SEG_G,             SEG_C | SEG_D | SEG_E | SEG_G, SEG_C | SEG_D | SEG_E,              SEG_C | SEG_E | SEG_G,              SEG_D | SEG_E | SEG_F | SEG_G,            0,                SEG_C | SEG_D | SEG_E | SEG_G,            SEG_A | SEG_E | SEG_F | SEG_G,            0,            SEG_A | SEG_C | SEG_D | SEG_F,  SEG_C | SEG_E | SEG_F | SEG_G,            SEG_C | SEG_D | SEG_E | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G,                SEG_A | SEG_C | SEG_D | SEG_F,                                                                                           
4 count of shots                SEG_G, SEG_A | SEG_C | SEG_D | SEG_E | SEG_F,           SEG_C | SEG_D | SEG_E | SEG_G,                SEG_G,                                                                                                                                                                                                                                                                                
-GO-                                                                                                                                                                                                                                                                                                                                                     
Menu 2                SEG_B | SEG_C,                0,            SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          SEG_E | SEG_F,                SEG_A | SEG_C | SEG_D | SEG_F,            SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,          SEG_D | SEG_E | SEG_F,                SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,        SEG_B | SEG_D | SEG_F | SEG_G,            0,            SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,            SEG_E | SEG_G,               SEG_E | SEG_F,                SEG_A | SEG_C | SEG_D | SEG_E | SEG_F,  SEG_C | SEG_E | SEG_F | SEG_G,            SEG_D | SEG_E | SEG_F | SEG_G,            SEG_C | SEG_E | SEG_G,                SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          SEG_A | SEG_C | SEG_D | SEG_F,            SEG_A | SEG_C | SEG_D | SEG_F,                 
1 D1splay Br1ghtness     SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,          0,            SEG_C | SEG_D | SEG_E | SEG_G,                SEG_A | SEG_C | SEG_D | SEG_F,            SEG_D | SEG_E | SEG_G,             SEG_E | SEG_F,                0,            SEG_D | SEG_E | SEG_G,               SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,        SEG_D | SEG_E | SEG_F,              SEG_E | SEG_F,  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,          SEG_E | SEG_G,               SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G, SEG_D | SEG_E | SEG_F | SEG_G,            SEG_E | SEG_F,                SEG_C | SEG_D | SEG_E | SEG_G,            SEG_C | SEG_E | SEG_G,                                                              
2 Osc1 cal1brat1on          SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,         0,            SEG_D | SEG_E | SEG_F | SEG_G,                SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          SEG_A | SEG_C | SEG_D | SEG_F,            SEG_D | SEG_E | SEG_F | SEG_G,            
*/

#endif
