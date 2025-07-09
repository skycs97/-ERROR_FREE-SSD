#include "nand_writer.h"

string NandWriter::write(int lba, string data)
{
	if (BUFFER_ENABLE) {
		bufferManager->addWriteCommand(lba, data);
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}