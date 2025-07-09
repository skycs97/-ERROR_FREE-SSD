#include "erase_command.h"

void EraseCommand::parseArg(int argc, const char* argv[])
{
	if (argc != ERASE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	int startLBA = atoi(argv[ARG_IDX_ERASE_START_ADDR]);
	int count = atoi(argv[ARG_IDX_ERASE_COUNT]);
	if (isInvalidAddress()) throw std::invalid_argument("Out of range");

	if (isInvalidEraseCount()) throw std::invalid_argument("Invalid erase LBA count");
	if (isInvalidEraseRange()) throw std::invalid_argument("The erase range exceeds the MAX_LBA");
}

bool EraseCommand::isInvalidAddress() {
	if ((startLBA < MIN_LBA) || (startLBA > MAX_LBA)) return true;
	return false;
}

bool EraseCommand::isInvalidEraseCount() {
	if ((count < 1) || (count > 10)) return true;
	return false;
}

bool EraseCommand::isInvalidEraseRange() {
	if ((startLBA + count - 1) > MAX_LBA) return true;
	return false;
}

string EraseCommand::run()
{
	if (BUFFER_ENABLE)
	{
		bufferManager->addEraseCommand(startLBA, count);
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	for (int i = startLBA; i < startLBA + count; i++)
	{
		datas[i] = "0x00000000";
	}
	nandFlashMemory->write(datas);

	return "COMPLETE_ERASE";
}