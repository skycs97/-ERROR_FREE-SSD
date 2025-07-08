#include "nand_reader.h"

string NandReader::read(int LBA)
{
	vector<string> datas = nandFlashMemory->read();
	return datas.at(LBA);
}
