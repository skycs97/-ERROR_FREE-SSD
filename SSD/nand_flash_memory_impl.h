#pragma once
#include "nand_flash_memory.h"

class NandFlashMemoryImpl : public NandFlashMemory {
public:
	NandFlashMemoryImpl() = default;
	string read(int LBA);
	string write(int lba, int data);
};
