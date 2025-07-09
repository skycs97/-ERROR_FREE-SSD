#pragma once
#include <string>
#include <iomanip>
#include <random>
#include <sstream>

using std::string;

class RandomNumberGenerator {
private:
	std::default_random_engine generator;
	std::uniform_int_distribution<unsigned int> distribution;

public:
	RandomNumberGenerator()
		: distribution(std::numeric_limits<unsigned int>::min(),
			std::numeric_limits<unsigned int>::max()) {
	}

	string generateRandomUnsignedIntString();

private:
	string hexToString(unsigned int random_value);
};