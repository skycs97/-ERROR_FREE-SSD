#pragma once
#include "global_config.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>

using std::string;
typedef int CMD_TYPE;

class ArgumentParser {
public:
	bool parse_args(int argc, const char* argv[]);

	CMD_TYPE getCmdType();
	int getAddr();
	int getSize();
	string getData();
	int getEraseStartAddr() { return nEraseStartAddr; }
	int getEraseCount() { return nEraseCount; }


	void setCmdType(CMD_TYPE cmdType) { eCmd = cmdType; }
	void setAddr(int addr) { nAddr = addr; }
	void setData(const string& data) { strData = data; }
	void setEraseStartAddr(int startAddr) { nEraseStartAddr = startAddr; }
	void setEraseCount(int nCount) { nEraseCount = nCount; }
	// stoul에서 변환 실패 시 std::invalid_argument 예외, 범위 초과 시 std::out_of_range 예외를 발생
	unsigned long parseHexAddress(const std::string& hexAddress);

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


	CMD_TYPE eCmd = NONE_CMD;
	CMD_TYPE eCmd = NONE_CMD;
	int nAddr = -1;
	int nSize = -1;
	string strData = "";
	int nEraseStartAddr = -1;
	int nEraseCount = -1;
};
