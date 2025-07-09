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
	if (argc != ERASE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::ERASE_CMD);

	parser.setEraseStartLBAAddr(atoi(argv[ARG_IDX_ERASE_START_ADDR]));
	if (isInvalidAddress(parser.getLBA())) throw std::invalid_argument("Out of range");

	parser.setEraseLBACount(atoi(argv[ARG_IDX_ERASE_COUNT]));
	if (isInvalidEraseCount(parser.getEraseLBACount())) throw std::invalid_argument("Invalid erase LBA count");
	if (isInvalidEraseRange(parser.getEraseStartLBA(), parser.getEraseLBACount())) throw std::invalid_argument("The erase range exceeds the MAX_LBA");

	return true;
}

bool NandEraser::isInvalidAddress(int nLBA) {
	if ((nLBA < MIN_LBA) || (nLBA > MAX_LBA)) return true;
	return false;
}

bool NandEraser::isInvalidEraseCount(int nEraseLBACount) {
	if ((nEraseLBACount < 1) || (nEraseLBACount > 10)) return true;
	return false;
}

bool NandEraser::isInvalidEraseRange(int nEraseStartLBA, int nEraseLBACount) {
	if ((nEraseStartLBA + nEraseLBACount - 1) > MAX_LBA) return true;
	return false;
}

string NandEraser::run()
{
	if (BUFFER_ENABLE)
	{
		bufferManager->addEraseCommand(parser.getEraseStartLBA(), parser.getEraseLBACount());
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	for (int i = parser.getEraseStartLBA(); i < parser.getEraseStartLBA() + parser.getEraseLBACount(); i++)
	{
		datas[i] = "0x00000000";
	}
	nandFlashMemory->write(datas);

	return "COMPLETE_ERASE";
}