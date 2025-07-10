#include <iostream>
#include "write_command.h"

namespace {
	const int numOfArgs = 2;
}

WriteCommand::WriteCommand(const std::vector<std::string>& args) : Command(CMD_WRITE, ::numOfArgs)
{
	LBA = args[0];
	value = args[1];
}

void WriteCommand::run(const CommandRunner& cmdRunner) const
{
	string result = cmdRunner.write(LBA, value);
	printResult(result);
}

void WriteCommand::printResult(const string& result) const
{
	std::cout << "[Write] ";
	if (result == "")
		std::cout << DONE;
	else
		std::cout << ERR;

	std::cout << std::endl << std::endl;
}

std::shared_ptr<Command> WriteCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_WRITE) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<WriteCommand>(new WriteCommand(args));
}
