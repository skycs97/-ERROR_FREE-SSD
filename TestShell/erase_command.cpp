#include <iostream>
#include "erase_command.h"

namespace {
	const int numOfArgs = 2;
}

EraseCommand::EraseCommand(const std::vector<std::string>& args) : Command(CMD_ERASE, ::numOfArgs)
{
	startLBA = args[0];
	LBARange = args[1];
}

void EraseCommand::run(const CommandRunner& cmdRunner) const
{
	if (checkLbaRange(stoi(startLBA), stoi(LBARange)) == false) {

		std::cout << "[Erase] WRONG LBA RANGE" << std::endl;
		return;
	}

	string result = cmdRunner.erase(startLBA, LBARange);
	printResult(result, startLBA + LBARange);
}

void EraseCommand::printResult(const string& result, const string& lba) const
{
	std::cout << "[Erase] ";

	if (result == ERASESUCCESS) {
		std::cout << DONE << std::endl;
	}
	else {
		std::cout << result << std::endl;
	}
}
void EraseCommand::printHelp() const
{
	std::cout << "** Erase Command **\n";
	std::cout << " - Erases data from the specified StartLBA in range of LBARange SSD.\n\n";
	std::cout << "Usage\n";
	std::cout << " erase [StartLBA] [LBARange]\n";
	std::cout << "Example\n";
	std::cout << " erase 0 10\n";
	std::cout << " erase 85 15\n";
}

bool EraseCommand::checkLbaRange(int startLBAIndex, int range) const
{
	if (isValidLba(startLBAIndex) == false) { return false; }
	if (isValidLba(range + startLBAIndex) == false) { return false; }

	return true;
}

std::shared_ptr<Command> EraseCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<EraseCommand>(new EraseCommand(args));
}