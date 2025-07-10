#include <iomanip>
#include "command_runner.h"
#include "write_read_aging_command.h"

namespace {
	const int numOfArgs = 0;
}

WriteReadAgingCommand::WriteReadAgingCommand(const std::vector<std::string>& args)
	:Command(CMD_3_WRITE_READ_AGING, ::numOfArgs)
{
}

void WriteReadAgingCommand::run(const CommandRunner& cmdRunner) const
{
	printProcess();

	RandomNumberGenerator rng;

	for (int i = 0; i < REPEAT_COUNT; i++) {

		string data = rng.generateRandomUnsignedIntString();

		if (WRITESUCCESS != cmdRunner.write(std::to_string(MIN_LBA), data))
			throw CommandRunFailException(FAIL);

		if (WRITESUCCESS != cmdRunner.write(std::to_string(MAX_LBA), data))
			throw CommandRunFailException(FAIL);

		if (cmdRunner.read(std::to_string(MIN_LBA)) != cmdRunner.read(std::to_string(MAX_LBA)))
			throw CommandRunFailException(FAIL);
	}

	printPass();
}

std::shared_ptr<Command> WriteReadAgingCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_3_WRITE_READ_AGING) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<WriteReadAgingCommand>(new WriteReadAgingCommand(args));
}
