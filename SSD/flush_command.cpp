#include "ssd_command.h"
#include "flush_command.h"

using std::string;

bool FlushCommand::flush()
{
	return false;
}

bool FlushCommand::parseArg(int argc, const char* argv[])
{
	if (argc != FLUSH_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	parser.setCmdType(CMD_FLUSH);

	return true;
}

string FlushCommand::run()
{
	return "NOT IMPLEMENTED YET";
}