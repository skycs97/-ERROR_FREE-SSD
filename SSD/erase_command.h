#pragma once

#include <string>
#include "nand_flash_memory.h"
#include "global_config.h"
#include "buffer_manager.h"
#include "ssd_command.h"

using std::string;

class EraseCommand : public SSDCommand {
public:
	EraseCommand(NandFlashMemory* nandFlashMemory, BufferManager* bufferManager)
		: nandFlashMemory{ nandFlashMemory }, bufferManager{ bufferManager } {
	}
	void parseArg(int argc, const char* argv[]) override;
	string run() override;
	
	void erase(int lba, int size);

private:
	bool isInvalidNumber(const string& str);
	bool isInvalidAddress();
	bool isInvalidEraseCount();
	bool isInvalidEraseRange();

	NandFlashMemory* nandFlashMemory;
	BufferManager* bufferManager;
	int startLBA;
	int count;
};