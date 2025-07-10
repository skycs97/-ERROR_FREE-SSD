#include "read_command.h"

using std::string;
using std::stoi;

bool ReadCommand::isInvalidNumber(const string& str) {
	return (str.find_first_not_of("0123456789") != string::npos);
}

void ReadCommand::parseArg(int argc, const char* argv[])
{
	if (argc != READ_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	if (isInvalidNumber(string(argv[ARG_IDX_ADDR]))) throw std::invalid_argument("Not a number in address");
	lba = stoi(argv[ARG_IDX_ADDR]);
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