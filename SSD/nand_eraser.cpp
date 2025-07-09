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
bool NandEraser::parseArg(int argc, const char* argv[])
{
	if (argc != 4) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::ERASE_CMD);

	parser.setEraseStartAddr(atoi(argv[ARG_IDX_ERASE_START_ADDR]));
	if ((parser.getEraseStartAddr() < MIN_LBA) || (parser.getEraseStartAddr() > MAX_LBA)) throw std::invalid_argument("Out of range");

	parser.setEraseCount(atoi(argv[ARG_IDX_ERASE_COUNT]));
	if ((parser.getEraseCount() < 1) || (parser.getEraseCount() > 10)) throw std::invalid_argument("Out of range");
	if ((parser.getEraseStartAddr() + parser.getEraseCount() - 1) > MAX_LBA) throw std::invalid_argument("Out of range");

	return true;
}

string NandEraser::run()
{
	if (BUFFER_ENABLE)
	{
		bufferManager->addEraseCommand(parser.getEraseStartAddr(), parser.getEraseCount());
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	for (int i = parser.getEraseStartAddr(); i < parser.getEraseStartAddr() + parser.getEraseCount(); i++)
	{
		datas[i] = "0x00000000";
	}
	nandFlashMemory->write(datas);

	return "";
}