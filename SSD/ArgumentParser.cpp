#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "ArgumentParser.h"

using std::string;

bool ArgumentParser::parse_args(int argc, const char* argv[])
{
	for (int argIdx = 1; argIdx < argc; ++argIdx)
	{
		if (argIdx == 1) {
			if ((argv[argIdx] == "R") || (argv[argIdx] == "r")) {
				eCmd = READ_CMD;
			}
			else if ((argv[argIdx] == "W") || (argv[argIdx] == "w")) {
				eCmd = WRITE_CMD;
			}
			else {
				throw std::invalid_argument("Invalid Command");
			}
		}

		if (argIdx == 2) {
			if ((eCmd == READ_CMD) || (eCmd == WRITE_CMD)) {
				nAddr = atoi(argv[argIdx]);

				if ((nAddr < 0) || (nAddr > 99)) throw std::invalid_argument("Out of range");
			}
		}

		if (argIdx == 3) {
			if (eCmd == WRITE_CMD) {
				dwData = static_cast<unsigned int>(parseHexAddress(string(argv[argIdx])));
			}
			else
			{
				throw std::invalid_argument("Invalid argument");
			}
		}
	}

	return true;
}

ArgumentParser::CMD_TYPE ArgumentParser::getCmdType()
{
	return eCmd;
}

int ArgumentParser::getAddr()
{
	return nAddr;
}

unsigned int ArgumentParser::getData()
{
	return dwData;
}

// stoul에서 변환 실패 시 std::invalid_argument 예외, 범위 초과 시 std::out_of_range 예외를 발생
unsigned long ArgumentParser::parseHexAddress(const std::string& hexAddress)
{
	// "0x" 접두사를 제거 (std::stoul은 자동으로 처리하지만, 명시적으로 제거해도 무방)
	std::string cleanedAddress = hexAddress;
	if (cleanedAddress.length() > 2 && (cleanedAddress.substr(0, 2) == "0x" || cleanedAddress.substr(0, 2) == "0X")) {
		cleanedAddress = cleanedAddress.substr(2);
	}
	return std::stoul(cleanedAddress, nullptr, 16);
}