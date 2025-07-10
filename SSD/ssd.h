#pragma once
#include "read_command.h"
#include "write_command.h"
#include "erase_command.h"
#include "nand_flash_memory.h"
#include "nand_flash_memory_impl.h"
#include "output_handler.h"
#include "file_handler.h"
#include "file_handler_impl.h"

class SSD
{
public:
	static SSD* getInstance(FileHandler* fileHandler = nullptr);  // Singleton
	void init();
	void run(int argc, const char* argv[]);

private:
	friend class SSDFactory;
	friend class SSDTestFactory;

	SSD(NandFlashMemory* nand, BufferManager* bufferManager,
		OutputHandler* outputHandler, SSDCommandFactory* commandFactory);
	~SSD();

	static SSD* instance;
	NandFlashMemory* nand;
	BufferManager* bufferManager;
	OutputHandler* outputHandler;
	SSDCommandFactory* factory;
};

class SSDFactory {
public:
	static SSD* createSSD()
	{
		FileHandler* fileHandler = new FileHandlerImpl();
		NandFlashMemory* nand = new NandFlashMemoryImpl(fileHandler);
		BufferManager* bufferManager = new BufferManager(nand, fileHandler);
		OutputHandler* outputHandler = new OutputHandler(fileHandler);
		SSDCommandFactory* factory = new SSDCommandFactory();

		return new SSD(nand, bufferManager, outputHandler, factory);
	}
};

class SSDTestFactory {
public:
	static SSD* createSSD(FileHandler* fileHandler)
	{
		NandFlashMemory* nand = new NandFlashMemoryImpl(fileHandler);
		BufferManager* bufferManager = new BufferManager(nand, fileHandler);
		OutputHandler* outputHandler = new OutputHandler(fileHandler);
		SSDCommandFactory* factory = new SSDCommandFactory();

		return new SSD(nand, bufferManager, outputHandler, factory);
	}
};