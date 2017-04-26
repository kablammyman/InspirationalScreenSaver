#ifndef BITMASK_H
#define BITMASK_H


class BitMask
{
public:
	static unsigned int createMask(unsigned int bitFlag);
	static int countBits(unsigned int n);
	static void printBits(unsigned int n);
	static bool isBitSet(unsigned int bit, unsigned int num);
	static void setBit(unsigned int bit, unsigned int & num);
};

#endif //BITMASK_H