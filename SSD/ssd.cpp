#include "ssd.h"

SSD& SSD::getInstance()
{
	static SSD instance;
	return instance;
}

SSD::SSD() {
	// Create utility instance
	FileHandler* fh = new FileHandler();
	outputHandler = new OutputHandler(fh);

	// Create IO instance
	nand = new NandFlashMemoryImpl(fh);
	reader = new NandReader(nand);
	writer = new NandWriter(nand);
}

SSD::~SSD() {
	delete reader;
	delete writer;
	delete nand;
}

void SSD::run()
{
}