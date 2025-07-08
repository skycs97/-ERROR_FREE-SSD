#include "nand_writer.h"

string NandWriter::write(int lba, string data)
{
	vector<string> datas;
	return nandFlashMemory->write(datas);
}