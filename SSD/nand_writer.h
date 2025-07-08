#pragma once
#include <string>
#include "nand_flash_memory.h"
#include "global_config.h"

using std::string;

class NandWriter
{
public:
	NandWriter(NandFlashMemory* nandFlashMemory)
		: nandFlashMemory{ nandFlashMemory } {}

	string write(int lba, string data);

private:
	bool isOutOfRange(int lba);

	NandFlashMemory* nandFlashMemory;
};