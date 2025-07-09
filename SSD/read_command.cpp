#include "read_command.h"

using std::string;

void ReadCommand::parseArg(int argc, const char* argv[])
{
	if (argc != READ_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	lba = atoi(argv[ARG_IDX_ADDR]);
	if (isInvalidAddress()) throw std::invalid_argument("Out of range");
}

bool ReadCommand::isInvalidAddress() {
	if ((lba < MIN_LBA) || (lba > MAX_LBA)) return true;
	return false;
}

string ReadCommand::run()
{
	if (BUFFER_ENABLE) {
		string ret = "";
		if (bufferManager->read(lba, ret) == true) {
			return ret;
		}
	}
	vector<string> datas = nandFlashMemory->read();
	return datas.at(lba);
}