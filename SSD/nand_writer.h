#pragma once
#include <string>
#include "nand_flash_memory.h"
#include "buffer_manager.h"
#include "global_config.h"

using std::string;

class NandWriter
{
public:
	NandWriter(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager) :
		nandFlashMemory{ nandFlashMemory },
		bufferManager{ bufferManager } {
	}

	string write(int lba, string data);

private:
	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
};