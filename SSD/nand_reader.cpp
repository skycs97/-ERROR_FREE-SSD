#include "nand_reader.h"
#include <stdexcept>
string NandReader::read(int LBA)
{
	if (LBA < 0 || LBA >= 100) throw std::range_error("LBA ���� 0�� 99 ������ ���̾�� �մϴ�.\n");
	return nandFlashMemory->read(LBA);
}
