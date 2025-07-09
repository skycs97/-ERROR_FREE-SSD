#pragma once
#include "nand_flash_memory.h"
#include "global_config.h"
#include "buffer_manager.h"

class NandEraser
{
public:
	NandEraser(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager)
		: nandFlashMemory{ nandFlashMemory }, bufferManager{ bufferManager } {
	}
	void erase(int lba, int size);

private:
	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
};