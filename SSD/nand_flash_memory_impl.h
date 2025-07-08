#pragma once
#include "nand_flash_memory.h"
#include "FileHandler.h"
#include "global_config.h"

class NandFlashMemoryImpl : public NandFlashMemory {
public:
	NandFlashMemoryImpl(FileHandler* fileHandler) :fileHandler{ fileHandler } {}

	vector<string> read() override;
	string write(const vector<string>& data) override;

private:
	FileHandler* fileHandler;
};
