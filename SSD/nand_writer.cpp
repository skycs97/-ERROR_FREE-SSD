#include "nand_writer.h"

string NandWriter::write(int lba, string data)
{
	if (isOutOfRange(lba)) return "ERROR";

	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}

bool NandWriter::isOutOfRange(int lba)
{
	return (lba < 0 || lba > 99);
}