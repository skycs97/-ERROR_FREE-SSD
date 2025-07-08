#include "ssd.h"

SSD& SSD::getInstance()
{
	static SSD instance;
	return instance;
}

SSD::SSD() {
	nand = new NandFlashMemoryImpl();
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