#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "ArgumentParser.h"

using std::string;

bool ArgumentParser::read_cmd_handler(int argc, const char* argv[])
{
	eCmd = READ_CMD;
	checkArgNum(argc);

	nAddr = atoi(argv[ARG_IDX_ADDR]);
	checkOutOfRange(nAddr);

	return true;
}

bool ArgumentParser::write_cmd_handler(int argc, const char* argv[])
{
	eCmd = WRITE_CMD;
	checkArgNum(argc);

	nAddr = atoi(argv[ARG_IDX_ADDR]);
	checkOutOfRange(nAddr);

	parseHexAddress(string(argv[ARG_IDX_DATA]));
	dwData = argv[ARG_IDX_DATA];

	return true;
}

bool ArgumentParser::erase_cmd_handler(int argc, const char* argv[])
{
	eCmd = ERASE_CMD;
	checkArgNum(argc);

	nAddr = atoi(argv[ARG_IDX_ADDR]);
	checkOutOfRange(nAddr);

	nSize = atoi(argv[ARG_IDX_DATA]);
	checkEraseRange(nAddr, nSize);

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

	if (isReadCmd(argv)) return read_cmd_handler(argc, argv);
	if (isWriteCmd(argv)) return write_cmd_handler(argc, argv);
	if (isEraseCmd(argv)) return erase_cmd_handler(argc, argv);
	
	return etc_cmd_handler(argc, argv);
}

ArgumentParser::CMD_TYPE ArgumentParser::getCmdType()
{
	return eCmd;
}

int ArgumentParser::getAddr()
{
	return nAddr;
}

int ArgumentParser::getSize()
{
	return nSize;
}

string ArgumentParser::getData()
{
	return dwData;
}

void ArgumentParser::checkArgNum(int argc)
{
	if (eCmd == READ_CMD)
	{
		if (argc != READ_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	}
	else if (eCmd == WRITE_CMD)
	{
		if (argc != WRITE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	}
	else if (eCmd == ERASE_CMD)
	{
		if (argc != ERASE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	}
}

void ArgumentParser::checkOutOfRange(int lba)
{
	if ((lba < MIN_LBA) || (lba > MAX_LBA)) throw std::invalid_argument("Out of range");
}

void ArgumentParser::checkEraseRange(int lba, int size)
{
	if (nAddr + nSize - 1 > MAX_LBA) throw std::invalid_argument("The erase range exceeds the MAX_LBA");
}

bool ArgumentParser::isReadCmd(const char* argv[])
{
	return (string(argv[ARG_IDX_CMD]) == string("R")) || (string(argv[ARG_IDX_CMD]) == string("r"));
}

bool ArgumentParser::isWriteCmd(const char* argv[])
{
	return (string(argv[ARG_IDX_CMD]) == string("W")) || (string(argv[ARG_IDX_CMD]) == string("w"));
}

bool ArgumentParser::isEraseCmd(const char* argv[])
{
	return (string(argv[ARG_IDX_CMD]) == string("E")) || (string(argv[ARG_IDX_CMD]) == string("e"));
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