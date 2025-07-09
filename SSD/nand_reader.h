#pragma once

#include <string>
#include "nand_flash_memory.h"
#include "buffer_manager.h"

using std::string;
class NandReader {
public:
	NandReader(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager):
		nandFlashMemory{ nandFlashMemory }, 
		bufferManager{ bufferManager } {
	}

	string read(int LBA);
private:
	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
};