#include "nand_writer.h"

string NandWriter::write(int lba, string data)
{
	if (lba < 0 || lba > 99) return "ERROR";

	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}