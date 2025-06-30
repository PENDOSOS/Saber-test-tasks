#include "1.h"
//#include <iostream>
#include <cmath>

#define BIT_SEQUENCE_LENGTH 32

void getInvertedBitSequenceFromNumber(const unsigned int* number, bool* bitSequence)
{
	unsigned int temp = *number;
	for (int i = 0; i < BIT_SEQUENCE_LENGTH; i++)
	{
		bitSequence[i] = temp % 2;
		temp = temp / 2;
		//std::cout << bitSequence[i];
	}
}

void getNumberFromBitSequence(unsigned int* number, bool* bitSequence)
{
	for (int i = 0; i < BIT_SEQUENCE_LENGTH; i++)
	{
		*number += (int)bitSequence[i] * (int)pow(2, BIT_SEQUENCE_LENGTH - 1 - i); // then count result of invertion
	}
}

const unsigned int* invertBitSequence(const unsigned int* inputNumber)
{
	unsigned int* result = new unsigned int;
	*result = 0;
	bool* bitSequence = new bool[BIT_SEQUENCE_LENGTH]; // representation of bit sequence
	getInvertedBitSequenceFromNumber(inputNumber, bitSequence);
	getNumberFromBitSequence(result, bitSequence);
	delete[] bitSequence;
	//std::cout << std::endl << *result;
	return result;
}