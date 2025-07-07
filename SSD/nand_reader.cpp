#include "nand_reader.h"
#include <stdexcept>
string NandReader::read(int LBA)
{
	if (LBA < 0 || LBA >= 100) throw std::range_error("The LBA must be a value between 0 and 99.\n");
	return nandFlashMemory->read(LBA);
}
