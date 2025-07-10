#include <string>
#include "erase_command.h"

using std::string;
using std::stoi;

bool EraseCommand::isInvalidNumber(const string& str) {
	return (str.find_first_not_of("0123456789") != string::npos);
}

void EraseCommand::parseArg(int argc, const char* argv[])
{
	if (argc != ERASE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	if (isInvalidNumber(string(argv[ARG_IDX_ERASE_START_ADDR]))) throw std::invalid_argument("Not a number in address");
	startLBA = stoi(argv[ARG_IDX_ERASE_START_ADDR]);

	if (isInvalidNumber(string(argv[ARG_IDX_ERASE_COUNT]))) throw std::invalid_argument("Not a number in count");
	count = stoi(argv[ARG_IDX_ERASE_COUNT]);

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

	return "";
}