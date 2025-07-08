#ifdef _DEBUG
#include "gmock/gmock.h"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
#include "ssd.h"
#include "nand_flash_memory.h"
#include "nand_flash_memory_impl.h"
#include "FileHandler.h"
#include "OutputHandler.h"

int main(int argc, char* argv[]) {
	// 1. Create IO and Flash instance
	FileHandler* fh = new FileHandler();
	NandFlashMemory* nand = new NandFlashMemoryImpl(fh);
	NandReader* reader = new NandReader(nand);
	NandWriter* writer = new NandWriter(nand);

	// 2. Create Utility instance
	OutputHandler* oh = new OutputHandler(fh);
	// TODO: Parser

	// 3. Create SSD instance
	SSD* ssd = new SSD(reader, writer, oh);

	// 4. Parsing command

	// 5. Process command
	ssd->run();
}
#endif