#include <limits.h> /* ULONG_MAX */
#include <stddef.h> /* size_t */
#include <stdio.h> /* sprintf */

/*#include "barr.h"*/

#define WORDSIZE (sizeof(size_t))

/* to turn a given idx bit on */
/* range is 0 to 63. if range of 'bit_idx' is out of range behavior is undefined */
unsigned long BArrSetOneBitOn(unsigned long bit_array, size_t bit_idx)
{
   /* shift 1 to left idx times */
    return (bit_array | (1UL << (bit_idx)));
}

/*********************************************************************/

/* to turn a given idx bit off */
/* range is 0 to 63. if range of 'bit_idx' is out of range behavior is undefined */
unsigned long BArrSetOneBitOff(unsigned long bit_array, size_t bit_idx)
{
    if (0 == ((bit_array >> bit_idx) & 1))
    {
        return (bit_array);
    }

   /* shift 1 to left idx times and xor it with the number */
    return ((bit_array ^ (1UL << (bit_idx))));
}

/*********************************************************************/

/* to turn all the bits on */
unsigned long BArrSetAllBitsOn(void)
{
    return (ULONG_MAX);
}

/*********************************************************************/

/* to turn all the bits off */
unsigned long BArrSetAllBitsOff(void)
{
    return (0);
}

/*********************************************************************/

/* to check if a given idx bit in unsigned long number is on */
/* range is 0 to 63. if range of 'bit_idx' is out of range behavior is undefined */
/* returns 1 if on, and 0 if off */
int BArrGetIsBitOn(unsigned long bit_array, size_t bit_idx)
{
     return ((bit_array >> (bit_idx)) & 1);
}

/*********************************************************************/

/* to check if a given idx bit in unsigned long number is off */
/* range is 0 to 63. if range of 'bit_idx' is out of range behavior is undefined */
/* returns 1 if off, and 0 if on */
int BArrGetIsBitOff(unsigned long bit_array, size_t bit_idx)
{
   /* find if the bit is on, and doing not on the result */
    return (!((bit_array >> (bit_idx)) & 1));
}

/*********************************************************************/

/* to turn a given idx bit to the value state */
/* range is 0 to 63. if range of 'bit_idx' is out of range behavior is undefined */
unsigned long BArrSetOneBitValue(unsigned long bit_array, size_t bit_idx, int state)
{
    if (0 == state)
    {
        if (0 == ((bit_array >> bit_idx) & 1))
        {
            return (bit_array);
        }

        /* if there is a needed to set the bit to 0 */
        return ((bit_array ^ (1UL << (bit_idx))));
    }
 
    /* if state is 1 */
    return (bit_array | (1UL << (bit_idx)));
}

/*********************************************************************/

/* to flip a given idx bit */
/* range is 0 to 63. if range of 'bit_idx' is out of range behavior is undefined */
unsigned long BArrFlipOneBit(unsigned long bit_array, size_t bit_idx)
{
   if (0 == ((bit_array >> bit_idx) & 1))
    {
        return (bit_array | (1UL << (bit_idx)));
    }

    /* if bit_idx is 1 */
    return ((bit_array ^ (1UL << (bit_idx))));
}

/*********************************************************************/

/* to flip a given all the bits in the unsigned long */
unsigned long BArrFlipAllBits(unsigned long bit_array)
{
    return (~bit_array);
}

/*********************************************************************/

/* to rotate a given ungigned long to_rotate times to the right */
unsigned long BArrRotateRight(unsigned long bit_array, size_t amount_to_rotate)
{
    unsigned long new_num = 0;
 
    /* to find the real index */
    amount_to_rotate %= (WORDSIZE * 8);
   
    /* to store the last amount_to_rotate bits of the rotation */
    new_num = bit_array >> amount_to_rotate;
    /* doing left shift to rotate the original array */
    bit_array <<= (WORDSIZE * 8 - amount_to_rotate);
   
    /* insert the bits that rotated */
    return (new_num | bit_array);
}

/*********************************************************************/

/* to rotate a given ungigned long to_rotate times to the left */
unsigned long BArrRotateLeft(unsigned long bit_array, size_t amount_to_rotate)
{
    unsigned long new_num = 0;
 
    /* to find the real index */
    amount_to_rotate %= (WORDSIZE * 8);
   
    /* to store the last (WORDSIZE * 8 - amount_to_rotate) bits of the rotation */
    new_num = bit_array >>  (WORDSIZE * 8 - amount_to_rotate);
    /* doing left shift to rotate the original array */
    bit_array <<= amount_to_rotate;
   
    /* insert the bits that rotated */
    return (new_num | bit_array);
}

/*********************************************************************/

/* to do a mirror for a given unsigned long */
unsigned long BArrMirrorBits(unsigned long bit_array)
{
    unsigned long new_num = 0;
    int i = 0;
 
    for (i = 0 ; i < WORDSIZE * 8 ; ++i)
    {
        /* checks the last bit */
        if (1 == (bit_array & 1))
        {
            new_num = (new_num << 1) | 1;
        }
        else
        {
            new_num = new_num << 1;
        }
        /* moving the number by right shift */
        bit_array >>= 1;
    }
 
    return (new_num);
}

/*********************************************************************/

/* to count how many bits are on */
size_t BArrCountBitsOn(unsigned long bit_array)
{
    size_t counter = 0;
 
    while (bit_array > 0)
    {
        ++counter;
        /* to turn off the next bit on */
        bit_array &= (bit_array - 1);
    }
 
    return (counter);
}

/*********************************************************************/

/* to count how many bits are off */
size_t BArrCountBitsOff(unsigned long bit_array)
{
    size_t counter = 0;
 
    while (bit_array > 0)
    {
        ++counter;
        bit_array &= (bit_array - 1);
    }
 
   /*the opposite of count on */
    return (WORDSIZE * 8 - counter);
}

/*********************************************************************/

/* to send the number to a string */
/* returns a pointer to the head of the string */
char *BArrToString(char *out_string, unsigned long bit_array)
{
    int i = 0;
    char *string_p = out_string;

    for (i = WORDSIZE * 8 - 1 ; i >= 0 ; --i)
    {
        sprintf(string_p, "%lu", ((bit_array >> i) & 1));
        ++string_p;    
    }
 
    return (out_string);
}

/*********************************************************************/

static size_t lut_table_count[256] = {0};

/* to set a table array for count bits on */
static void SetCountLUT()
{
    size_t i = 1;
   
    if (lut_table_count[1] == 0)
    {
        for (i = 1 ; i < 256 ; ++i)
        {
            lut_table_count[i] = BArrCountBitsOn(i);
        }
    }
}

/* to count bits on with a table array */
size_t BArrLUTCountBitsOn(unsigned long bit_array)
{
    size_t every_byte = 0; /* the byte that we want to check */
    size_t counter = 0;
    size_t i = 0;
   
    SetCountLUT();
   
    for (i = 0 ; (i < 8) && (bit_array > 0) ; ++i)
    {
        every_byte = bit_array & 0xff;
        counter += lut_table_count[every_byte];
        /* decrease by WORDSIZE for the next check */
        bit_array >>= 8;
    }
   
    return (counter);
}

/*********************************************************************/

static unsigned char lut_table_mirror[256] = {0};

/* to set a table array for mirror a number */
static void SetMirrorLUT()
{
    size_t i = 1;
    size_t j = 0;
    unsigned char new_num = 0;
    unsigned char num_for_table = 0;
  
    if (lut_table_mirror[1] == 0)
    {
        for (i = 1 ; i < 256 ; ++i)
        {
            num_for_table = i;
            for (j = 0 ; j < 8 ; ++j)
            {
                /* checks the last bit */
                if (1 == (num_for_table & 1))
                {
                    new_num = (new_num << 1) | 1;
                }
                else
                {
                    new_num = new_num << 1;
                }
                /* moving the number by right shift */
                num_for_table >>= 1;
            }
            lut_table_mirror[i] = new_num;
        }
    }
}

/* to do the mirror with a table map */
unsigned long BArrLUTMirror(unsigned long bit_array)
{
    size_t every_byte = 0; 			/* the byte that we want to check */
    unsigned long new_num = 0;
    size_t i = 0;
  
    SetMirrorLUT();
  
    for (i = 0 ; i < 8 ; ++i)
    {
        every_byte = bit_array & 0xff;
        new_num <<= 8;
        new_num |= lut_table_mirror[every_byte];
        /* decrease by 8 for the next check */
        bit_array >>= 8;      
    }

    return (new_num);
}

/*********************************************************************/
