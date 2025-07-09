#pragma once
#include <string>
#include "nand_flash_memory.h"
#include "buffer_manager.h"
#include "global_config.h"
#include "SSDCommand.h"
using std::string;

class NandWriter : public SSDCommand
{
public:
	NandWriter(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager) :
		nandFlashMemory{ nandFlashMemory },
		bufferManager{ bufferManager } {
	}

	string write(int lba, string data);

	virtual bool parseArg(int argc, const char* argv[]) override;
	virtual string run() override;
private:
	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
	ArgumentParser parser;
};