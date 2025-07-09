#include "nand_eraser.h"

void NandEraser::erase(int lba, int size)
{
	if (BUFFER_ENABLE)
	{
		bufferManager->addEraseCommand(lba, size);
		return;
	}

	vector<string> datas = nandFlashMemory->read();
	for (int i = lba; i < lba + size; i++)
	{
		datas[i] = "0x00000000";
	}
	nandFlashMemory->write(datas);
	return;
}