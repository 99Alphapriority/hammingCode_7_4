#include <stdio.h>
#include <stdlib.h>
#include "hamming_calculations.h"
#include "hamming_validation.h"

U8 codeGenerated = 0;
U8 isCodeGenerated = 0;

int generateHammingCode(void)
{
	UInt32 input;
	codeGenerated = 0;
	fprintf(stderr,"Input data bits having value <0-15>\n");
	scanf("%d", &input);

	fprintf(stderr,"Input data in binary:\n");
	print_bin((U8)input);

	codeGenerated = hamming_code((U8)input);

	if ((0 == codeGenerated) && (0!= input))
		return 1;

	fprintf(stderr,"Hamming code for the given data:\n");
	print_bin(codeGenerated);
	fprintf(stderr,"decimal value: %d\n",codeGenerated);
	isCodeGenerated++;
}

U8 checkHammingCode(void)
{
	UInt32 input1, input2, option;
	U8 errorCode;
    fflush(stdin);

	if(isCodeGenerated)
	{
		fprintf(stderr,"Choose option: \n1. Use previously generated code? \n2. Use new code?\n");
		scanf("%d",&input1);
		switch(input1)
		{
			case 1:
					validateHammingCode(codeGenerated);
					break;

			case 2:
					fprintf(stderr,"Input a Hamming code in Decimal format\n");
					scanf("%d", &input2);
					validateHammingCode((U8) input2);
					break;

			default:
					return 1;

		}
	}
	else
	{
		fprintf(stderr,"Input a Hamming code in Decimal format\n");
		scanf("%d",&input1);
		validateHammingCode((U8) input1);
		return 0;
	}
	fflush(stdin);
}

int main()
{	
	UInt32 option = 0;
	U8 input = 0;

	do{
		fprintf(stderr,"Choose option: \n1. Generate Hamming Code \n2. Check Hamming Code \n");
		scanf("%d", &option);

		switch(option)
		{
			case 1: 
					generateHammingCode();
					break;

			case 2: 
					checkHammingCode();
					break;

			default: 
					return 1;

		}

		fflush(stdin);
		fprintf(stderr,"Try again? [y/n] \t");
		input = getc(stdin);
		fprintf(stderr,"\n");

	}while(('y' == input) || ('Y' == input));

	return 0;
}
