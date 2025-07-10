#include <iomanip>
#include "command_runner.h"
#include "erase_and_write_aging.h"

namespace {
	const int numOfArgs = 0;
}

EraseAndWriteAgingCommand::EraseAndWriteAgingCommand(const std::vector<std::string>& args)
	:Command(CMD_4_ERASE_AND_WRITE_AGING, ::numOfArgs)
{
}

void EraseAndWriteAgingCommand::run(const CommandRunner& cmdRunner) const
{
	printProcess();
	int startLBA = MIN_LBA;
	int LBARange = 3;

	cmdRunner.erase(std::to_string(startLBA), std::to_string(LBARange));

	for (int i = 0; i < REPEAT_COUNT; i++) {
		for (startLBA = (MIN_LBA + 2); startLBA <= (MAX_LBA - 1); startLBA+=2) {

			if (WRITESUCCESS != writeTwiceRandomData(cmdRunner, startLBA))
				throw CommandRunFailException(FAIL);

			LBARange = getLbaRange(startLBA);

			if (ERASESUCCESS != cmdRunner.erase(std::to_string(startLBA), std::to_string(LBARange)))
				throw CommandRunFailException(FAIL);
		}
	}

	printPass();
}

string EraseAndWriteAgingCommand::writeTwiceRandomData(const CommandRunner& cmdRunner, int startLBA) const
{
	string result = WRITESUCCESS;
	RandomNumberGenerator rng;

	if (WRITESUCCESS != cmdRunner.write(std::to_string(startLBA), rng.generateRandomUnsignedIntString()))
		result = ERR;

	if (WRITESUCCESS != cmdRunner.write(std::to_string(startLBA), rng.generateRandomUnsignedIntString()))
		result = ERR;

	return result;
}

int EraseAndWriteAgingCommand::getLbaRange(int startLBA) const {
	int LBARange = 3;

	if (startLBA == MAX_LBA - 1)
		LBARange = 2;

	return LBARange;
}

void EraseAndWriteAgingCommand::printHelp() const
{
	std::cout << "** Erase Write Aging Command **\n";
	std::cout << " - A test that erase & writes a random value to LBA 0 and 99, repeated 30 times..\n";
	std::cout << "Usage\n";
	std::cout << " 4_EraseAndWriteAging\n";
	std::cout << " 4_\n";
}

std::shared_ptr<Command> EraseAndWriteAgingCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	return std::make_shared<EraseAndWriteAgingCommand>(args);
}
