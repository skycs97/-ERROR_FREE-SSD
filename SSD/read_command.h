#pragma once

#include <string>
#include "nand_flash_memory.h"
#include "buffer_manager.h"
#include "ssd_command.h"

using std::string;
class ReadCommand : public SSDCommand {
public:
	ReadCommand(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager):
		nandFlashMemory{ nandFlashMemory }, 
		bufferManager{ bufferManager } {
	}
	
	virtual bool parseArg(int argc, const char* argv[]) override;
	virtual string run() override;

	string read(int LBA);
private:
	bool isInvalidAddress(int nLBA);

	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
	ArgumentParser parser;
};