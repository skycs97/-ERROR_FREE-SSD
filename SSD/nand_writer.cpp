#include "nand_writer.h"

string NandWriter::write(int lba, string data)
{
	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}