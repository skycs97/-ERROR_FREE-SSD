#include "ssd_command.h"
#include "flush_command.h"

using std::string;

void FlushCommand::parseArg(int argc, const char* argv[])
{
	if (argc != FLUSH_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
}

string FlushCommand::run()
{
	bufferManager->flush();
	return "";
}