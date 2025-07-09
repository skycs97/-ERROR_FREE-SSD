#include "nand_reader.h"

string NandReader::read(int LBA)
{
	if (BUFFER_ENABLE) {
		string ret = "";
		if (bufferManager->read(LBA, ret) == true) {
			return ret;
		}
	}
	vector<string> datas = nandFlashMemory->read();
	return datas.at(LBA);
}
