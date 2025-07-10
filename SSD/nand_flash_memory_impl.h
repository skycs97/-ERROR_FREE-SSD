#pragma once
#include "nand_flash_memory.h"
#include "file_handler.h"
#include "global_config.h"

class NandFlashMemoryImpl : public NandFlashMemory {
public:
	NandFlashMemoryImpl(FileHandler* fileHandler) :fileHandler{ fileHandler } {}

	void init() override;
	vector<string> read() override;
	string write(vector<string>& data) override;

private:
	FileHandler* fileHandler;

	vector<string> convertToLines(const char* data);
};
