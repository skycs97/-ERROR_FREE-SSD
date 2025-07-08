#include "nand_writer.h"
#include <stdexcept>

string NandWriter::write(int lba, string data)
{
	if (isOutOfRange(lba)) throw std::range_error("The LBA must be a value between 0 and 99.\n");

	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}

bool NandWriter::isOutOfRange(int lba)
{
	return (lba < 0 || lba > 99);
}