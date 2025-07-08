#include "ssd.h"
#include <stdexcept>

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
	string data = "";
	try {
		argumentParser->parse_args(argc, argv);
		switch (argumentParser->getCmdType()) {
		case ArgumentParser::READ_CMD: {
			int addr = argumentParser->getAddr();
			data = reader->read(addr);
			break;
		}
		case ArgumentParser::WRITE_CMD: {
			int addr = argumentParser->getAddr();
			string data = argumentParser->getData();
			writer->write(addr, data);
			break;
		}
		default: {
			throw std::invalid_argument("unknown type");
			return;
		}
		}
	}
	catch (std::exception e) {
		data = "ERROR";
	}
	outputHandler->output(data);
}