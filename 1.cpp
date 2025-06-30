// Approximate time - 1 hour

#include "1.h"
#include <iostream>
#include <cmath>

#define BIT_SEQUENCE_LENGTH 32

const uint32_t invertBitSequence(const uint32_t inputNumber)
{
	uint32_t result = 0;
	for (int i = 0; i < BIT_SEQUENCE_LENGTH; i++)
	{
		int invertedBit = (inputNumber >> i) & 1;
		std::cout << invertedBit;
		result |= invertedBit << (BIT_SEQUENCE_LENGTH - 1 - i);
	}
	std::cout << std::endl << result;
	return result;
}