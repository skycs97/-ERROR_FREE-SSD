#pragma once

#include <string>
#include "nand_flash_memory.h"
#include "buffer_manager.h"
#include "ssd_command.h"

using std::string;
class ReadCommand : public SSDCommand {
public:
	ReadCommand(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager):
		nandFlashMemory{ nandFlashMemory }, 
		bufferManager{ bufferManager } {
	}
	
	void parseArg(int argc, const char* argv[]) override;
	string run() override;

private:
	bool isInvalidAddress();
	bool isInvalidNumber(const string& str);

	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;

	int lba;
};