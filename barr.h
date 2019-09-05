
/********************************************************************/
/*                            BARR                                  */
/********************************************************************/
#include <stddef.h>

#ifndef WS1_h

#define WS1_h

/* to turn a given idx bit on */
unsigned long BArrSetOneBitOn(unsigned long bit_array, size_t bit_idx);
/*********************************************************************/

/* to turn a given idx bit off */
unsigned long BArrSetOneBitOff(unsigned long bit_array, size_t bit_idx);
/*********************************************************************/

/* to turn all the bits on */
unsigned long BArrSetAllBitsOn(void);
/*********************************************************************/

/* to turn long all the bits off */
unsigned long BArrSetAllBitsOff(void);
/*********************************************************************/

/* to check if a given idx bit is on */
int BArrGetIsBitOn(unsigned long bit_array, size_t bit_idx);
/*********************************************************************/

/* to check if a given idx bit is off */
int BArrGetIsBitOff(unsigned long bit_array, size_t bit_idx);
/*********************************************************************/

/* to turn a given idx bit to the state val */
unsigned long BArrSetOneBitValue(unsigned long bit_array, size_t bit_idx, int state);
/*********************************************************************/

/* to flip a given idx bit */
unsigned long BArrFlipOneBit(unsigned long bit_array, size_t bit_idx);
/*********************************************************************/

/* to flip a given all the bits in the unsigned long */
unsigned long BArrFlipAllBits(unsigned long bit_array);
/*********************************************************************/

/* to rotate a given ungigned long to_rotate times to the left */
unsigned long BArrRotateLeft(unsigned long bit_array, size_t amount_to_rotate);
/*********************************************************************/

/* to rotate a given ungigned long to_rotate times to the left */
unsigned long BArrRotateRight(unsigned long bit_array, size_t amount_to_rotate);
/*********************************************************************/

/* to do a mirror for a given ungigned long */
unsigned long BArrMirrorBits(unsigned long bit_array);
/*********************************************************************/

/* to count how many bits are on */
size_t BArrCountBitsOn(unsigned long bit_array);
/*********************************************************************/

/* to count how many bits are off */
size_t BArrCountBitsOff(unsigned long bit_array);
/*********************************************************************/

/* to send the number to a string */
/* returns a pointer to the head of the string */
char *BArrToString(char *out_string, unsigned long bit_array);
/*********************************************************************/

/* to count bits on with a table array */
size_t BArrLUTCountBitsOn(unsigned long bit_array);
/*********************************************************************/

/* to do the mirror with a table map */
unsigned long BArrLUTMirror(unsigned long bit_array);


#endif



