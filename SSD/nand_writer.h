#pragma once
#include <string>
#include "nand_flash_memory.h"

using std::string;

class NandWriter
{
public:
	NandWriter(NandFlashMemory* nandFlashMemory)
		: nandFlashMemory{ nandFlashMemory } {}

	string write(int lba, string data);

private:
	static const int MIN_LBA = 0;
	static const int MAX_LBA = 99;

	bool isOutOfRange(int lba);

	NandFlashMemory* nandFlashMemory;
};