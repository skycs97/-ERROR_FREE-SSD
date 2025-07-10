#include "partial_LBA_write_command.h"
#include "logger.h"

namespace {
	const int numOfArgs = 0;
};
PartialLBAWriteCommand::PartialLBAWriteCommand(const std::vector<std::string>& cmd)
	:Command(CMD_2_PARTIAL_LBA_WRITE, ::numOfArgs)
{
}
bool PartialLBAWriteCommand::checkResult(const vector<std::string>& result) const
{
	string firstItem = result[0];

	for (const std::string& resultitem : result)
	{
		if (resultitem != firstItem) { return false; }
	}
	return true;
}


void PartialLBAWriteCommand::run(const CommandRunner& cmdRunner) const
{
	printProcess();

	for (int testRepeat = 0; testRepeat < REPEAT_COUNT; testRepeat++) {
		vector<std::string> result;

		for (std::string Lba : TestLbaList) {
			cmdRunner.write(Lba, WRITE_DATA);
		}

		for (std::string Lba : TestLbaList) {

			result.push_back(cmdRunner.read(Lba));
		}

		if (checkResult(result) == false) {
			throw CommandRunFailException(FAIL);
		}

		LOGGING_SHELL( "Repeat : " + std::to_string(testRepeat) + ", Result : " + std::to_string(checkResult(result)));
	}

	printPass();
}

std::shared_ptr<Command> PartialLBAWriteCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_2_PARTIAL_LBA_WRITE) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<PartialLBAWriteCommand>(new PartialLBAWriteCommand(args));
}
