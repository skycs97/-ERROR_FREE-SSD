#include "full_write_and_read_compare_command.h"

namespace {
	const int numOfArgs = 0;
}

FullWriteAndReadCompareCommand::FullWriteAndReadCompareCommand(const std::vector<std::string>& args) 
	: Command(CMD_1_FULL_WRITE_AND_READ_COMPARE, ::numOfArgs){
}

void FullWriteAndReadCompareCommand::run(const CommandRunner& cmdRunner) const
{
	printProcess();

	int lba = 0;
	int testSize = 5;
	std::vector<string> testValue = { "0xA5A5A5A5", "0x5A5A5A5A", "0xFFFFFFFF", "0xF0F0F0F0", "0x0F0F0F0F" };

	while (lba <= MAX_LBA) {

		if (partialWrite(cmdRunner, lba, testSize, testValue[0]) == false)
			throw TestScriptFailExcpetion(FAIL);

		if (partialRead(cmdRunner, lba, testSize) == false)
			throw TestScriptFailExcpetion(FAIL);

		lba += testSize;

		if (partialWrite(cmdRunner, lba, testSize, testValue[0]) == false)
			throw TestScriptFailExcpetion(FAIL);

		if (partialRead(cmdRunner, lba, testSize) == false)
			throw TestScriptFailExcpetion(FAIL);

		lba += testSize;
	}

	std::cout << "Pass" << std::endl;
}

bool FullWriteAndReadCompareCommand::partialWrite(const CommandRunner& cmdRunner, int lba, int testSize, string data) const
{
	int totalResult = true;
	for (int i = 0; i < testSize; i++) {
		if (WRITESUCCESS == cmdRunner.write(std::to_string(lba + i), data))
			continue;
		totalResult = false;
	}

	return totalResult;
}

bool FullWriteAndReadCompareCommand::partialRead(const CommandRunner& cmdRunner, int lba, int testSize) const
{
	int totalResult = true;
	for (int i = 0; i < testSize; i++) {
		if (ERROR != cmdRunner.read(std::to_string(lba + i)))
			continue;
		totalResult = false;
	}

	return totalResult;
}

void FullWriteAndReadCompareCommand::printHelp() const
{
	std::cout << "** Full Write And Read Compare Command **\n";
	std::cout << " - Test command to compare after writing 5 LBAs each and reading them\n";
	std::cout << "Usage\n";
	std::cout << " 1_FullWriteAndReadCompare\n";
	std::cout << " 1_\n";
}

void FullWriteAndReadCompareCommand::printProcess() const
{
	std::cout << std::left << std::setw(25) << cmdName;
	std::cout << "  ___   " << "Run..";
}

std::shared_ptr<Command> FullWriteAndReadCompareCommandFactory::makeCommand(const string& cmdName
																			, const std::vector<string>& args)
{
	if (args.size() != numOfArgs) return nullptr;
	return std::make_shared<FullWriteAndReadCompareCommand>(args);
}
