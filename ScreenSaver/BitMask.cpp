#include <stdio.h>
#include "BitMask.h"

unsigned int BitMask::createMask(unsigned int bitFlag)
{
	/*unsigned int returnVal = 0x00000001;
	for(unsigned int i = 0; i < bitFlag; i++)
		returnVal *= 2;*/
	
	unsigned int returnVal = 0x00000000;	
	returnVal |= (1<<bitFlag);

	return returnVal;
}

int BitMask::countBits(unsigned int n)
{
	int counter = 0;
	for(int i = 0; i < (sizeof(unsigned long)*8); i++)
	{
		if ((n >> i) & 1)
			counter++;
	}
	return counter;
}


void BitMask::printBits(unsigned int n)
{
	for(int i = 0; i < (sizeof(unsigned long)*8); i++)
	{
		if ((n >> i) & 1)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

bool BitMask::isBitSet(unsigned int bit, unsigned int num)
{
	return ((1 << bit) & num);
}

void BitMask::setBit(unsigned int bit, unsigned int & num)
{
	 num |= 1 << bit;
}

/*
int main()
{
	//i guess this only works with cout?
	//printf("print binary: %u\n", std::bitset<16>((int)16));
	printf("%d\n",sizeof(unsigned long long)*8);
	unsigned int someInt = 1;
	BitMask::printBits(someInt);
	printf("\n------------------------\n");
	//int first_third_and_fourth = (1 << 0) | (1 << 2) | (1 << 3);
	unsigned int mask = BitMask::createMask(2);
	someInt |= mask;
	BitMask::printBits(mask);
	printf("\n------------------------\n");
	BitMask::printBits(someInt);
	printf("num bits: %d\n",BitMask::countBits(someInt));
	return 0;
}*/
