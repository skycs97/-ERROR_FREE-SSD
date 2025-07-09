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
	if (isInvalidAddress(parser.getAddr())) throw std::invalid_argument("Out of range");

	parser.setEraseCount(atoi(argv[ARG_IDX_ERASE_COUNT]));
	if (isInvalidEraseCount(parser.getEraseLBACount())) throw std::invalid_argument("Invalid erase LBA count");
	if (isInvalidEraseRange(parser.getEraseStartAddr(), parser.getEraseLBACount())) throw std::invalid_argument("The erase range exceeds the MAX_LBA");

	return true;
}

bool NandEraser::isInvalidAddress(int nLBA) {
	if ((nLBA < MIN_LBA) || (nLBA > MAX_LBA)) return false;
	return true;
}

bool NandEraser::isInvalidEraseCount(int nEraseLBACount) {
	if ((nEraseLBACount < 1) || (nEraseLBACount > 10)) return false;
	return true;
}

bool NandEraser::isInvalidEraseRange(int nEraseStartAddr, int nEraseLBACount) {
	if ((nEraseStartAddr + nEraseLBACount - 1) > MAX_LBA) return false;
	return true;
}

string NandEraser::run()
{
	if (BUFFER_ENABLE)
	{
		bufferManager->addEraseCommand(parser.getEraseStartAddr(), parser.getEraseLBACount());
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	for (int i = parser.getEraseStartAddr(); i < parser.getEraseStartAddr() + parser.getEraseLBACount(); i++)
	{
		datas[i] = "0x00000000";
	}
	nandFlashMemory->write(datas);

	return "COMPLETE_ERASE";
}