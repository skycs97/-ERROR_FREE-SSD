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

bool EraseCommand::checkLbaRange(int startLBAIndex, int range) const
{
	if (isValidLba(startLBAIndex) == false) { return false; }
	if (isValidLba(range + startLBAIndex -1) == false) { return false; }

	return true;
}

std::shared_ptr<Command> EraseCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_ERASE) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<EraseCommand>(new EraseCommand(args));
}