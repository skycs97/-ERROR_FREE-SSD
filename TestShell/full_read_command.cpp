#include <iomanip>
#include "full_read_command.h"
#include <string>
#include "logger.h"

namespace {
	const int numOfArgs = 0;
}

FullReadCommand::FullReadCommand(const std::vector<std::string>& args) : Command(CMD_FULLREAD, ::numOfArgs)
{
}

void FullReadCommand::run(const CommandRunner& cmdRunner) const
{
	string result;
	std::cout << "[Full Read]" << std::endl;
	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		result = cmdRunner.read(std::to_string(lba));
		printResult(result, std::to_string(lba));
		LOGGING_SHELL( result);
	}
}
void FullReadCommand::printResult(const string& result, const string& lba) const
{
	std::cout << "LBA " << std::right << std::setw(2) << std::setfill('0') << lba << " : ";
	std::cout << result << std::endl;
}

std::shared_ptr<Command> FullReadCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_FULLREAD) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<FullReadCommand>(new FullReadCommand(args));
}
