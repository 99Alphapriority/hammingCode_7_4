#include "hamming_validation.h"
#include <stdio.h>

U8 validateHammingCode(U8 hammingCode)
{
	/* Explanation
	
		errors can be detected using the following parity equations:

			check 1: c1 ^ c2 ^ c3 ^ c5 = 0
			cehck 2: c1 ^ c3 ^ c4 ^ c6 = 0
			check 3: c1 ^ c2 ^ c4 ^ c7 - 0

		_________________________________________
		|	|	check1 |	check2 |	check3 	|
		_________________________________________	
		|c1	|	fail   |	fail   |	fail	|
		|c2	|	fail   |	pass   |	fail	|
		|c3	|	fail   |	fail   |	pass	|
		|c4	|	pass   |	fail   |	fail	|
		|c5	|	fail   |	pass   |	pass	|
		|c6	|	pass   |	fail   |	pass	|
		|c7	|	pass   |	pass   |	fail	|
		_________________________________________

		observations:
			1.	If only 1 check fails	->	error in parity bits c5, c6 or c7
			2.	If 2 checks fail		->	error in data bits c2, c3 or c4
			3.	If all checks fail		->	error in data bit c1

		Step 1:
				extract the c7 bit from the given hamming code using AND operation.
				right sift the hamming code.
				Repeat until c1.
		Step 2:
				compute the value of check 1, check 2 and check 3 using the parity equations.
		step 3:
				using the above mentioned table, check which bit has error.

	*/

	U8 c1,c2,c3,c4,c5,c6,c7;
	U8 check1, check2, check3;

	fprintf(stderr,"Hamming code provided: \n");
	print_bin(hammingCode);

	c7 = checkBitValue(hammingCode);
	hammingCode >>= 1;

	c6 = checkBitValue(hammingCode);
	hammingCode >>= 1;

	c5 = checkBitValue(hammingCode);
	hammingCode >>= 1;

	c4 = checkBitValue(hammingCode);
	hammingCode >>= 1;

	c3 = checkBitValue(hammingCode);
	hammingCode >>= 1;

	c2 = checkBitValue(hammingCode);
	hammingCode >>= 1;

	c1 = checkBitValue(hammingCode);
	hammingCode >>= 1;

	if(0 != hammingCode)
	{
		fprintf(stderr,"Provided hamming code is greater than 15.\n");
		return 1;
	}

	check1 = c1 ^ c2 ^ c3 ^ c5;
	check2 = c1 ^ c3 ^ c4 ^ c6;
	check3 = c1 ^ c2 ^ c4 ^ c7;

	if(0 != check1)
	{
		if(0 != check2)
		{
			if(0 != check3)
			{
				fprintf(stderr,"Error in 2nd bit from left \(c1\). \n");
				return 0;
			}
			else
			{
				fprintf(stderr,"Error in 4th bit from left \(c3\). \n");
				return 0;
			}
		}
		else if(0 != check3)
		{
			fprintf(stderr,"Error in 3rd bit from left \(c2\). \n");
			return 0;
		}
		else
		{
			fprintf(stderr,"Error in 6th bit from left \(c5\). \n");
			return 0;
		}
	}
	else if(0 != check2)
	{
		if(0 != check3)
		{
			fprintf(stderr,"Error in 5th bit from left \(c4\). \n");
			return 0;
		}
		else
		{
			fprintf(stderr,"Error in 7th bit from left \(c6\). \n");
			return 0;
		}
	}
	else if(0 != check3)
	{
		fprintf(stderr,"Error in 8th bit from left \(c7\). \n");
		return 0;
	}
	else
	{
		fprintf(stderr,"There is no error in the Hamming code provided\n");
		return 0;
	}
}




