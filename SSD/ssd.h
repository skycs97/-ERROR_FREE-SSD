#pragma once
#include "nand_reader.h"
#include "nand_writer.h"
#include "nand_eraser.h"
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

	NandReader* reader;
	NandWriter* writer;
	NandEraser* eraser;
	NandFlashMemory* nand;
	BufferManager* bufferManager;
	OutputHandler* outputHandler;
	ArgumentParser* argumentParser;
	SSDCommandFactory* factory;
};