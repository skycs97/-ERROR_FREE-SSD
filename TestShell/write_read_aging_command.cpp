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

	for (int i = 0; i < 200; i++) {

		string data = rng.generateRandomUnsignedIntString();

		if (WRITESUCCESS != cmdRunner.write(std::to_string(MIN_LBA), data))
			throw TestScriptFailExcpetion(FAIL);

		if (WRITESUCCESS != cmdRunner.write(std::to_string(MAX_LBA), data))
			throw TestScriptFailExcpetion(FAIL);

		if (cmdRunner.read(std::to_string(MIN_LBA)) != cmdRunner.read(std::to_string(MAX_LBA)))
			throw TestScriptFailExcpetion(FAIL);
	}

	std::cout << "Pass" << std::endl;
}

void WriteReadAgingCommand::printHelp() const
{
	std::cout << "** Write Read Aging Command **\n";
	std::cout << " - A test that writes a random value to LBA 0 and 99 and then reads it to confirm, repeated 200 times..\n";
	std::cout << "Usage\n";
	std::cout << " 3_WriteReadAging\n";
	std::cout << " 3_\n";
}

std::shared_ptr<Command> WriteReadAgingCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;
	return std::make_shared<WriteReadAgingCommand>(args);
}
