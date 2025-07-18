#pragma once
#include <string>
#include <stdexcept>
#include "nand_flash_memory.h"
#include "buffer_manager.h"

using std::string;

class SSDCommand {
public:
	virtual void parseArg(int argc, const char* argv[]) = 0;
	virtual string run() = 0;
};

class SSDCommandFactory {
public:
	SSDCommand* createCommand(const string& cmdName, NandFlashMemory* nandFlashMemory, BufferManager* bufferManager);

private:
	bool isReadCmd(const string& cmdName);
	bool isWriteCmd(const string& cmdName);
	bool isEraseCmd(const string& cmdName);
	bool isFlushCmd(const string& cmdName);
};

