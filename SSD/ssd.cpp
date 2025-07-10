#include "ssd.h"
#include "buffer_manager.h"
#include <stdexcept>
#include "ssd_command.h"

SSD::SSD(FileHandler* fileHandler) {
	// Create result IO instance
	outputHandler = new OutputHandler(fileHandler);

	// Create nand IO instance
	nand = new NandFlashMemoryImpl(fileHandler);
	bufferManager = new BufferManager(nand, fileHandler);
	factory = new SSDCommandFactory();
	// FIXME: 내부적으로 std::exception 사용하나, 현재 위치는 try-catch 문 밖
	bufferManager->init();
}

SSD::~SSD() {
	delete bufferManager;
}

void SSD::run(int argc, const char* argv[])
{
	string result = "";
	try {
		outputHandler->init();
		nand->init();
		
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