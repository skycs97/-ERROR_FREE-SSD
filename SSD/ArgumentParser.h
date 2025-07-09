#pragma once
#include "global_config.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

using std::string;

class ArgumentParser {
public:
	enum CMD_TYPE {
		NONE_CMD = 0,
		READ_CMD = 1,
		WRITE_CMD = 2,
		ERASE_CMD = 3,
	};

	bool parse_args(int argc, const char* argv[]);

	CMD_TYPE getCmdType();
	int getAddr();
	int getSize();
	string getData();

private:
	bool read_cmd_handler(int argc, const char* argv[]);
	bool write_cmd_handler(int argc, const char* argv[]);
	bool erase_cmd_handler(int argc, const char* argv[]);
	bool etc_cmd_handler(int argc, const char* argv[]);
	void checkArgNum(int argc);
	void checkOutOfRange(int lba);
	void checkEraseRange(int lba, int size);
	bool isReadCmd(const char* argv[]);
	bool isWriteCmd(const char* argv[]);
	bool isEraseCmd(const char* argv[]);

	// stoul���� ��ȯ ���� �� std::invalid_argument ����, ���� �ʰ� �� std::out_of_range ���ܸ� �߻�
	unsigned long parseHexAddress(const std::string& hexAddress);

	CMD_TYPE eCmd = NONE_CMD;
	int nAddr = -1;
	int nSize = -1;
	string dwData = "";
};
