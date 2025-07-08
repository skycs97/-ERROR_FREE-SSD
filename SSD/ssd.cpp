#include "ssd.h"

SSD::SSD(FileHandler* fileHandler) {
	// Create result IO instance
	outputHandler = new OutputHandler(fileHandler);
	// Create nand IO instance
	nand = new NandFlashMemoryImpl(fileHandler);
	reader = new NandReader(nand);
	writer = new NandWriter(nand);

	argumentParser = new ArgumentParser();
}

SSD::~SSD() {
	delete reader;
	delete writer;
	delete nand;
}

void SSD::run(int argc, const char* argv[])
{
	argumentParser->parse_args(argc, argv);
	string data="";
	switch (argumentParser->getCmdType()) {
	case ArgumentParser::READ_CMD: {
		int addr = argumentParser->getAddr();
		data = reader->read(addr);
		break;
	}
	case ArgumentParser::WRITE_CMD: {
		break;
	}
	default: {
		return;
	}
	}
	outputHandler->output(data);
}