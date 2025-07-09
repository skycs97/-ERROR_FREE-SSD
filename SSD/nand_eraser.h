#pragma once

#include <string>
#include "nand_flash_memory.h"
#include "global_config.h"
#include "buffer_manager.h"
#include "ssd_command.h"

using std::string;

class NandEraser : public SSDCommand {
public:
	NandEraser(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager)
		: nandFlashMemory{ nandFlashMemory }, bufferManager{ bufferManager } {
	}
	virtual bool parseArg(int argc, const char* argv[]) override;
	virtual string run() override;
	
	void erase(int lba, int size);

private:

	bool isInvalidAddress(int nLBA);
	bool isInvalidEraseCount(int nEraseLBACount);
	bool isInvalidEraseRange(int nEraseStartLBA, int nEraseLBACount);

	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
	ArgumentParser parser;	
};