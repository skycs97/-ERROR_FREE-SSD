#pragma once
#include "nand_reader.h"
#include "nand_writer.h"
#include "nand_flash_memory.h"
#include "nand_flash_memory_impl.h"
#include "OutputHandler.h"
#include "FileHandler.h"

class SSD
{
public:
	static SSD& getInstance();
	~SSD();
	void run();

private:
	SSD();
	SSD(const SSD& other) = delete;
	SSD& operator=(const SSD& other) = delete;

	NandReader* reader;
	NandWriter* writer;
	NandFlashMemory* nand;
	OutputHandler* outputHandler;
};