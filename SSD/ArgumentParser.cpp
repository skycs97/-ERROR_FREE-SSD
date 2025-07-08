#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "ArgumentParser.h"

using std::string;

bool ArgumentParser::read_cmd_handler(int argc, const char* argv[])
{
	if (argc != 3) throw std::invalid_argument("number of argument is incorrect");

	eCmd = READ_CMD;
	nAddr = atoi(argv[ARG_IDX_ADDR]);
	if ((nAddr < 0) || (nAddr > 99)) throw std::invalid_argument("Out of range");

	return true;
}

bool ArgumentParser::write_cmd_handler(int argc, const char* argv[])
{
	if (argc != 4) throw std::invalid_argument("number of argument is incorrect");

	eCmd = WRITE_CMD;
	nAddr = atoi(argv[ARG_IDX_ADDR]);
	if ((nAddr < MIN_LBA) || (nAddr > MAX_LBA)) throw std::invalid_argument("Out of range");

	parseHexAddress(string(argv[ARG_IDX_DATA]));
	dwData = argv[ARG_IDX_DATA];
	return true;
}

bool ArgumentParser::etc_cmd_handler(int argc, const char* argv[])
{
	throw std::invalid_argument("Invalid Command");

	return true;
}

bool ArgumentParser::parse_args(int argc, const char* argv[])
{
	if (argc < MIN_ARG_CNT) throw std::invalid_argument("no command");

	if ((string(argv[ARG_IDX_CMD]) == string("R")) || (string(argv[ARG_IDX_CMD]) == string("r"))) {
		return read_cmd_handler(argc, argv);
	}
	else if ((string(argv[ARG_IDX_CMD]) == string("W")) || (string(argv[ARG_IDX_CMD]) == string("w"))) {
		return write_cmd_handler(argc, argv);
	}
	else {
		return etc_cmd_handler(argc, argv);
	}
}

ArgumentParser::CMD_TYPE ArgumentParser::getCmdType()
{
	return eCmd;
}

int ArgumentParser::getAddr()
{
	return nAddr;
}

string ArgumentParser::getData()
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