#pragma once
#include "global_config.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

using std::string;

#define CMD_TYPE int

class ArgumentParser {
public:

	// stoul에서 변환 실패 시 std::invalid_argument 예외, 범위 초과 시 std::out_of_range 예외를 발생
	unsigned long parseHexAddress(const std::string& hexAddress);

private:
	CMD_TYPE nCmdType = CMD_INVALID;
	int nLBA = -1;
	int nLBACount = -1;
	string strData = "";
	int nEraseStartLBA = -1;
	int nEraseLBACount = -1;
};
