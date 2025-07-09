#pragma once
#include "nand_flash_memory.h"

class NandEraser
{
public:
	NandEraser(NandFlashMemory* nandFlashMemory) : nandFlashMemory{ nandFlashMemory } {}
	void erase(int lba, int size);

private:
	NandFlashMemory* nandFlashMemory;
};