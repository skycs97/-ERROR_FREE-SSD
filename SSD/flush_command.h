#pragma once

#include <string>
#include "nand_flash_memory.h"
#include "ssd_command.h"
#include "buffer_manager.h"

using std::string;
class FlushCommand : public SSDCommand {
public:
	FlushCommand(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager) :
		nandFlashMemory{ nandFlashMemory }, bufferManager{ bufferManager } {
	}
	virtual void parseArg(int argc, const char* argv[]) override;
	virtual string run() override;
private:
	
	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
};