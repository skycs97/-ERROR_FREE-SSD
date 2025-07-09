#include "read_command.h"

using std::string;

string ReadCommand::read(int LBA)
{
	if (BUFFER_ENABLE) {
		string ret = "";
		if (bufferManager->read(LBA, ret) == true) {
			return ret;
		}
	}
	vector<string> datas = nandFlashMemory->read();
	return datas.at(LBA);
}

bool ReadCommand::parseArg(int argc, const char* argv[])
{
	if (argc != READ_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(CMD_READ);
	parser.setLBA(atoi(argv[ARG_IDX_ADDR]));

	if (isInvalidAddress(parser.getLBA())) throw std::invalid_argument("Out of range");

	return true;
}

bool ReadCommand::isInvalidAddress(int nLBA) {
	if ((nLBA < MIN_LBA) || (nLBA > MAX_LBA)) return true;
	return false;
}

string ReadCommand::run()
{
	int addr = parser.getLBA();
	return read(addr);	
}