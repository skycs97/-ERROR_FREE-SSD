#pragma once
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
	};

	bool parse_args(int argc, const char* argv[]);

	CMD_TYPE getCmdType();
	int getAddr();
	string getData();

private:
	bool read_cmd_handler(int argc, const char* argv[]);
	bool write_cmd_handler(int argc, const char* argv[]);
	bool etc_cmd_handler(int argc, const char* argv[]);

	// stoul���� ��ȯ ���� �� std::invalid_argument ����, ���� �ʰ� �� std::out_of_range ���ܸ� �߻�
	unsigned long parseHexAddress(const std::string& hexAddress);

	CMD_TYPE eCmd = NONE_CMD;
	int nAddr = -1;
	string dwData = "";

	const int ARG_IDX_CMD = 1;
	const int ARG_IDX_ADDR = 2;
	const int ARG_IDX_DATA = 3;
};
