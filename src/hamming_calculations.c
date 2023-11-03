#include <stdio.h>
#include "hamming_calculations.h"

void print_bin(U8 value)
{
	for(int i = sizeof(char)*7; i>=0; i--)
	{
		fprintf(stderr,"%d",(value & (1<<i))>>i);
	}
	fprintf(stderr,"\n");
}

U8 checkBitValue(U8 value)
{
	if(value & 1)
		return 1;
	else
		return 0;
}

U8 setParityBit(U8 *value)
{
	U8 parityBit = 0;
	
	if(1 == *value)
		parityBit = 1;
	else 
		parityBit = 0;
	
	//Reset the value to 0
	*value = 0;

	return parityBit;
}
	
U8 hamming_code(U8 input)
{
	/* Explanation:
		Hamming Code: [c1 c2 c3 c4 c5 c6 c7]

		c1,c2,c3,c4 ---> data bits
		c5,c6,c7	---> parity bits

		equation 1: c1 ^ c2 ^ c3 ^ c5 = 0
		equation 2: c1 ^ c3 ^ c4 ^ c6 = 0
		equation 3: c1 ^ c2 ^ c4 ^ c7 = 0

		step 1:
			calculate the value of c1, c2, c3 and c4 from the input

		step 2:
			calculate the value of c5, c6 and c7 by performing XOR operations in the following manner:

				c5 = calculated so that c5 satisfies equation 1
				c6 = calculated so that c6 satisfies equation 2
				c7 = calculated so that c7 satisfies equation 3

		step 3:
			left shift the input by 1 at a time and append the value of parity bits at the end.
	*/

	U8 c1, c2, c3, c4, c5, c6, c7;
	U8 tmp;

	tmp = input;
	
	c4 = checkBitValue(tmp);
	tmp >>= 1;

	c3 = checkBitValue(tmp);
	tmp >>= 1;

	c2 = checkBitValue(tmp);
	tmp >>= 1;

	c1 = checkBitValue(tmp);
	tmp >>= 1;

	if(0 != tmp)
	{
		fprintf(stderr,"ERORR!!!!! Input is greater than 15.\n");
		return 0;
	}

	tmp = c1 ^ c2 ^ c3;
	c5 = setParityBit(&tmp);
	input <<= 1;
	input |= c5;

	tmp = c1 ^ c3 ^ c4;
	c6 = setParityBit(&tmp);
	input <<= 1;
	input |= c6;

	tmp = c1 ^ c2 ^ c4;
	c7 = setParityBit(&tmp);
	input <<= 1;
	input |= c7;

	return input;
	
}
