#include "full_write_command.h"
#include "logger.h"

namespace {
	const int numOfArgs = 1;
};

FullWriteCommand::FullWriteCommand(const std::vector<std::string>& args) : Command(CMD_FULLWRITE, ::numOfArgs)
{
	value = args[0];
}

void FullWriteCommand::run(const CommandRunner& cmdRunner) const
{
	string writeResult;
	string fullWriteResult = "";

	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		writeResult = cmdRunner.write(std::to_string(lba), this->value);
		if (writeResult == ERR)
			fullWriteResult = ERR;
	}

	printResult(fullWriteResult);
	LOGGING_SHELL( " Result : " + writeResult);
}

void FullWriteCommand::printResult(const string& result) const
{
	std::cout << "[Full Write] ";
	if (result == "")
		std::cout << DONE;
	else
		std::cout << ERR;

	std::cout << std::endl << std::endl;
}

std::shared_ptr<Command> FullWriteCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_FULLWRITE) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<FullWriteCommand>(new FullWriteCommand(args));
}
