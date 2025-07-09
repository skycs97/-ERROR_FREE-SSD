#include "ssd.h"
#include "buffer_manager.h"
#include <stdexcept>

SSD::SSD(FileHandler* fileHandler) {
	// Create result IO instance
	outputHandler = new OutputHandler(fileHandler);
	// Create nand IO instance
	nand = new NandFlashMemoryImpl(fileHandler);
	BufferManager* bufferManager = new BufferManager(nand, fileHandler);
	reader = new NandReader(nand, bufferManager);
	writer = new NandWriter(nand, bufferManager);
	eraser = new NandEraser(nand, bufferManager);

	argumentParser = new ArgumentParser();
}

SSD::~SSD() {
	delete reader;
	delete writer;
	delete nand;
}

void SSD::run(int argc, const char* argv[])
{
	string result = "";
	try {
		outputHandler->getFileHandler()->init();

		argumentParser->parse_args(argc, argv);
		switch (argumentParser->getCmdType()) {
		case ArgumentParser::READ_CMD: {
			int addr = argumentParser->getAddr();
			result = reader->read(addr);
			break;
		}
		case ArgumentParser::WRITE_CMD: {
			int addr = argumentParser->getAddr();
			string data = argumentParser->getData();
			writer->write(addr, data);
			break;
		}
		case ArgumentParser::ERASE_CMD: {
			int addr = argumentParser->getAddr();
			int size = argumentParser->getSize();
			eraser->erase(addr, size);
			result = "COMPLETE_ERASE";
			break;
		}
		default: {
			throw std::invalid_argument("unknown type");
			return;
		}
		}
	}
	catch (std::exception e) {
		result = "ERROR";
	}
	outputHandler->output(result);
}