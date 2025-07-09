#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "ArgumentParser.h"

using std::string;

bool ArgumentParser::read_cmd_handler(int argc, const char* argv[])
{
	eCmd = CMD_READ;
	checkArgNum(argc);

	nLBA = atoi(argv[ARG_IDX_ADDR]);
	checkOutOfRange(nLBA);

	return true;
}

bool ArgumentParser::write_cmd_handler(int argc, const char* argv[])
{
	eCmd = CMD_WRITE;
	checkArgNum(argc);

	nLBA = atoi(argv[ARG_IDX_ADDR]);
	checkOutOfRange(nLBA);

	parseHexAddress(string(argv[ARG_IDX_DATA]));
	strData = argv[ARG_IDX_DATA];

	return true;
}

bool ArgumentParser::erase_cmd_handler(int argc, const char* argv[])
{
	eCmd = CMD_ERASE;
	checkArgNum(argc);

	nLBA = atoi(argv[ARG_IDX_ADDR]);
	checkOutOfRange(nLBA);

	nLBACount = atoi(argv[ARG_IDX_DATA]);
	checkEraseRange(nLBA, nLBACount);

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

CMD_TYPE ArgumentParser::getCmdType()
{
	return eCmd;
}

int ArgumentParser::getLBA()
{
	return nLBA;
}

int ArgumentParser::getLBACount()
{
	return nLBACount;
}

string ArgumentParser::getData()
{
	return strData;
}

void ArgumentParser::checkArgNum(int argc)
{
	if (eCmd == CMD_READ)
	{
		if (argc != READ_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	}
	else if (eCmd == CMD_WRITE)
	{
		if (argc != WRITE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	}
	else if (eCmd == CMD_ERASE)
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
	if (nLBA + nLBACount - 1 > MAX_LBA) throw std::invalid_argument("The erase range exceeds the MAX_LBA");
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