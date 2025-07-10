#include <iomanip>
#include "full_read_command.h"
#include <iomanip>
#include <string>
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
	}
}
void FullReadCommand::printResult(const string& result, const string& lba) const
{
	std::cout << "LBA " << std::setw(2) << std::setfill('0') << lba << " : ";
	std::cout << result << std::endl;
}

void FullReadCommand::printHelp() const
{
	std::cout << "** Full Read Command **\n";
	std::cout << " - Read value from the all LBAs in SSD.\n";
	std::cout << " - LBA (" << MIN_LBA << " ~ " << MAX_LBA << ")\n\n";
	std::cout << "Usage\n";
	std::cout << " fullread\n";
}

std::shared_ptr<Command> FullReadCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;
	return std::make_shared<FullReadCommand>(args);
}
