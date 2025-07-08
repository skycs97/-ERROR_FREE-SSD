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

// stoul���� ��ȯ ���� �� std::invalid_argument ����, ���� �ʰ� �� std::out_of_range ���ܸ� �߻�
unsigned long ArgumentParser::parseHexAddress(const std::string& hexAddress)
{
	// "0x" ���λ縦 ���� (std::stoul�� �ڵ����� ó��������, ��������� �����ص� ����)
	std::string cleanedAddress = hexAddress;
	if (cleanedAddress.length() > 2 && (cleanedAddress.substr(0, 2) == "0x" || cleanedAddress.substr(0, 2) == "0X")) {
		cleanedAddress = cleanedAddress.substr(2);
	}
	return std::stoul(cleanedAddress, nullptr, 16);
}