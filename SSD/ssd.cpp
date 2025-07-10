#include "ssd.h"
#include "buffer_manager.h"
#include <stdexcept>
#include "ssd_command.h"

SSD* SSD::instance = nullptr;

SSD* SSD::getInstance(FileHandler* fileHandler) {
	if (instance == nullptr) {
		if (fileHandler == nullptr)
			instance = SSDFactory::createSSD();
		else
			instance = SSDTestFactory::createSSD(fileHandler);
	}
	return instance;
}

SSD::SSD(NandFlashMemory* nand, BufferManager* bufferManager,
	OutputHandler* outputHandler, SSDCommandFactory* commandFactory)
{
	this->nand = nand;
	this->bufferManager = bufferManager;
	this->outputHandler = outputHandler;
	this->factory = commandFactory;
}

SSD::~SSD() {
	delete nand;
	delete bufferManager;
	delete outputHandler;
	delete factory;
}

void SSD::init()
{
	bufferManager->init();
	outputHandler->init();
	nand->init();
}

void SSD::run(int argc, const char* argv[])
{
	string result = "";
	try {
		init();
		
		SSDCommand* cmd = nullptr;	
		if (argc > 1) {
			cmd = factory->createCommand(argv[ARG_IDX_CMD], nand, bufferManager);
			cmd->parseArg(argc, argv);
			result = cmd->run();
		} else throw std::invalid_argument("Invalid Command");
	}
	catch (std::exception e) {
		result = "ERROR";
	}
	outputHandler->output(result);
}