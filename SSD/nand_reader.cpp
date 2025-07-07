#include "nand_reader.h"
#include <stdexcept>
string NandReader::read(int LBA)
{
	if (LBA < 0 || LBA >= 100) throw std::range_error("LBA 값은 0과 99 사이의 값이어야 합니다.\n");
	return nandFlashMemory->read(LBA);
}
