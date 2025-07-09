#include "nand_writer.h"

string NandWriter::write(int lba, string data)
{
	bufferManager->addWriteCommand(lba, data); 
	// (buffer 동작시 아래 로직은 지웁니다.)
	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}