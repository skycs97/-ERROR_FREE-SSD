#pragma once
#include "nand_flash_memory.h"
#include "FileHandler.h"
class NandFlashMemoryImpl : public NandFlashMemory {
public:
	NandFlashMemoryImpl(FileHandler* fileHandler) :fileHandler{ fileHandler } {}

	vector<string> read() override;
	string write(const vector<string>& data) override;
private:
	const string NAND_FILENAME = "ssd_nand.txt";
	FileHandler* fileHandler;
};
