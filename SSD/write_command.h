#pragma once
#include <string>
#include "nand_flash_memory.h"
#include "buffer_manager.h"
#include "global_config.h"
#include "ssd_command.h"
using std::string;

class WriteCommand : public SSDCommand
{
public:
	WriteCommand(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager) :
		nandFlashMemory{ nandFlashMemory },
		bufferManager{ bufferManager } {
	}

	void parseArg(int argc, const char* argv[]) override;
	string run() override;
private:
	bool isInvalidNumber(const string& str);
	bool isInvalidHexNumber(const string& str);
	bool isInvalidAddress();
	void validDataOrThrow();

	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;

	int lba = 0;
	string data;
};