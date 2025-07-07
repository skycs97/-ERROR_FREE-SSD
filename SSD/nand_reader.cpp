#include "nand_reader.h"

int NandReader::read(int LBA)
{
	return nandFlashMemory->read(LBA);
}
