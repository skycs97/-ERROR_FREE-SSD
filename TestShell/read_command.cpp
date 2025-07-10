#include <iostream>
#include "read_command.h"

namespace {
	const int numOfArgs = 1;
}

ReadCommand::ReadCommand(const std::vector<std::string>& args) : Command(CMD_READ, ::numOfArgs)
{
	LBA = args[0];
}

void ReadCommand::run(const CommandRunner& cmdRunner) const
{
	string result = cmdRunner.read(LBA);
	printResult(result, LBA);
}

void ReadCommand::printResult(const string& result, const string& lba) const
{
	std::cout << "[Read] ";
	if (result != ERR)
		std::cout << lba << " : ";
	std::cout << result
		<< std::endl << std::endl;
}

std::shared_ptr<Command> ReadCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_READ) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<ReadCommand>(new ReadCommand(args));
}