#include "SSDCommand.h"
#include "nand_flush.h"

using std::string;

bool NandFlush::flush()
{
	return false;
}

bool NandFlush::parseArg(int argc, const char* argv[])
{
	if (argc != FLUSH_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	parser.setCmdType(ArgumentParser::FLUSH_CMD);

	return true;
}

string NandFlush::run()
{
	return "NOT IMPLEMENTED YET";
}