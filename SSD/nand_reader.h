#pragma once

#include "nand_flash_memory.h"
class NandReader {
public:
	NandReader(NandFlashMemory* nandFlashMemory) : nandFlashMemory{ nandFlashMemory } {}

	int read(int LBA);
private:
	NandFlashMemory* nandFlashMemory;
};