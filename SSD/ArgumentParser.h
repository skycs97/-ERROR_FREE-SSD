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
		FLUSH_CMD = 4,
	};

	CMD_TYPE getCmdType();
	int getLBA();
	int getLBACount();
	string getData();
	int getEraseStartLBA();
	int getEraseLBACount();

	void setCmdType(CMD_TYPE cmdType);
	void setLBA(int addr);
	void setData(const string& data);
	void setEraseStartLBAAddr(int startAddr);
	void setEraseLBACount(int nCount);

	// stoul에서 변환 실패 시 std::invalid_argument 예외, 범위 초과 시 std::out_of_range 예외를 발생
	unsigned long parseHexAddress(const std::string& hexAddress);

private:
	CMD_TYPE eCmd = NONE_CMD;
	int nLBA = -1;
	int nLBACount = -1;
	string strData = "";
	int nEraseStartLBA = -1;
	int nEraseLBACount = -1;
};
