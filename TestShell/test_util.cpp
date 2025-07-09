#include "test_util.h"

string RandomNumberGenerator::generateRandomUnsignedIntString() 
{
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
