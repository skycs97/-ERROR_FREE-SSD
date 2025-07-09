#pragma once

#include <string>
#include "nand_flash_memory.h"
#include "ssd_command.h"
#include "buffer_manager.h"

using std::string;
class NandFlush : public SSDCommand {
public:
	NandFlush(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager) :
		nandFlashMemory{ nandFlashMemory }, bufferManager{ bufferManager } {
	}
	virtual bool parseArg(int argc, const char* argv[]) override;
	virtual string run() override;

	bool flush();
private:
	
	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
	ArgumentParser parser;
};