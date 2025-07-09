#include "SSDCommand.h"
#include "nand_flush.h"

using std::string;

bool NandFlush::flush()
{
	return false;
}

bool NandFlush::parseArg(int argc, const char* argv[])
{
	if (argc != 3) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::READ_CMD);
	parser.setLBA(atoi(argv[ARG_IDX_ADDR]));

	if ((parser.getLBA() < MIN_LBA) || (parser.getLBA() > MAX_LBA)) throw std::invalid_argument("Out of range");

	return true;
}

string NandFlush::run()
{
	return "";
}