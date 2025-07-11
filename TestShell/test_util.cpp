#include "test_util.h"

string RandomNumberGenerator::generateRandomUnsignedIntString() 
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, 0xFFFFFFFF);

	return hexToString(distribution(generator));
}

string RandomNumberGenerator::hexToString(unsigned int random_value)
{
	std::stringstream ss;
	ss << "0x" << std::hex
		<< std::uppercase
		<< std::setw(8) << std::setfill('0')
		<< random_value;

	return ss.str();
}
