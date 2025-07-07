#pragma once

#include <string>
#include "nand_flash_memory.h"

using std::string;
class NandReader {
public:
	NandReader(NandFlashMemory* nandFlashMemory) : nandFlashMemory{ nandFlashMemory } {}

	string read(int LBA);
private:
	NandFlashMemory* nandFlashMemory;
};