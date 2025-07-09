#pragma once
#include "read_command.h"
#include "write_command.h"
#include "erase_command.h"
#include "nand_flash_memory.h"
#include "nand_flash_memory_impl.h"
#include "output_handler.h"
#include "file_handler.h"
#include "argument_parser.h"

class SSD
{
public:
	SSD(FileHandler* fileHandler);
	~SSD();

	void run(int argc, const char* argv[]);
private:
	NandFlashMemory* nand;
	BufferManager* bufferManager;
	OutputHandler* outputHandler;
	ArgumentParser* argumentParser;
	SSDCommandFactory* factory;
};