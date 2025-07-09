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

	// stoul���� ��ȯ ���� �� std::invalid_argument ����, ���� �ʰ� �� std::out_of_range ���ܸ� �߻�
	unsigned long parseHexAddress(const std::string& hexAddress);

private:
	CMD_TYPE nCmdType = CMD_INVALID;
	int nLBA = -1;
	int nLBACount = -1;
	string strData = "";
	int nEraseStartLBA = -1;
	int nEraseLBACount = -1;
};
