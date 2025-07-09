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
	
	virtual void parseArg(int argc, const char* argv[]) override;
	virtual string run() override;

private:
	bool isInvalidAddress();

	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;

	int lba;
};