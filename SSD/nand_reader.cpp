#include "nand_reader.h"

using std::string;

string NandReader::read(int LBA)
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

bool NandReader::parseArg(int argc, const char* argv[])
{
	if (argc != READ_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::READ_CMD);
	parser.setLBA(atoi(argv[ARG_IDX_ADDR]));

	if (isInvalidAddress(parser.getLBA())) throw std::invalid_argument("Out of range");

	return true;
}

bool NandReader::isInvalidAddress(int nLBA) {
	if ((nLBA < MIN_LBA) || (nLBA > MAX_LBA)) return true;
	return false;
}

string NandReader::run()
{
	int addr = parser.getLBA();
	return read(addr);	
}