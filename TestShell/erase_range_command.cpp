#include <iostream>
#include "erase_range_command.h"

namespace {
	const int numOfArgs = 2;
}

EraseRangeCommand::EraseRangeCommand(const std::vector<std::string>& args) : Command(CMD_ERASE_RANGE, ::numOfArgs)
{
	startLBA = args[0];
	endLBA = args[1];
}

void EraseRangeCommand::run(const CommandRunner& cmdRunner) const
{
	if (stoi(endLBA) < stoi(startLBA)) {
		printResult(ERR, startLBA + endLBA);
		return;
	}

	int rangeNum = stoi(endLBA) - stoi(startLBA) + 1;
	string result = cmdRunner.erase(startLBA, std::to_string(rangeNum));

	printResult(result, startLBA + endLBA);
}

void EraseRangeCommand::printResult(const string& result, const string& lba) const
{
	std::cout << "[EraseRange] ";

	if (result == ERR) {
		std::cout << ERR << std::endl;
	}
	else if (result == ERASESUCCESS) {
		std::cout << DONE << std::endl;
	}
	else {
		std::cout << FAIL << std::endl;
	}
}
void EraseRangeCommand::printHelp() const
{
	std::cout << "** Erase Range Command **\n";
	std::cout << " - Erases data from the specified StartLBA to EndLBA SSD.\n\n";
	std::cout << "Usage\n";
	std::cout << " erase_range [StartLBA] [endLBA]\n";
	std::cout << "Example\n";
	std::cout << " erase_range 0 9\n";
	std::cout << " erase_range 85 99\n";
}

std::shared_ptr<Command> EraseRangeCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;
	return std::make_shared<EraseRangeCommand>(args);
}