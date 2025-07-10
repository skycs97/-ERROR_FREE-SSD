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
void WriteCommand::printHelp() const
{
	std::cout << "** Write Command **\n";
	std::cout << " - Writes value to the specified LBA of SSD.\n\n";
	std::cout << "Usage\n";
	std::cout << " write [LBA] [value]\n";
	std::cout << "Example\n";
	std::cout << " write 0 0xAAAABBBB\n";
	std::cout << " write 10 0x10002000\n";
}

std::shared_ptr<Command> WriteCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;
	return std::shared_ptr<WriteCommand>(new WriteCommand(args));
}
