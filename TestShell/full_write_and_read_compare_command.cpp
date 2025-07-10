#include "full_write_and_read_compare_command.h"
#include "logger.h"

namespace {
	const int numOfArgs = 0;
}

FullWriteAndReadCompareCommand::FullWriteAndReadCompareCommand(const std::vector<std::string>& args) 
	: Command(CMD_1_FULL_WRITE_AND_READ_COMPARE, ::numOfArgs){
}

void FullWriteAndReadCompareCommand::run(const CommandRunner& cmdRunner) const
{
	printProcess();

	int lba = MIN_LBA;
	int testSize = 5;
	int random = 1;

	std::vector<string> testValue;

	while (lba <= MAX_LBA) {
		LOGGING_SHELL( " LBA : " + std::to_string(lba));

		testValue = getTestData(testSize, random);

		if (partialWrite(cmdRunner, lba, testSize, testValue) == false)
			throw CommandRunFailException(FAIL);

		if (partialReadAndCompare(cmdRunner, lba, testSize, testValue) == false)
			throw CommandRunFailException(FAIL);

		lba += testSize;

		LOGGING_SHELL( 
			"Test Value: " + testValue[0] + ", " + testValue[1] + ", " + testValue[2] + ", " + testValue[3] + ", " + testValue[4]);
	}

	printPass();
}

bool FullWriteAndReadCompareCommand::partialWrite(const CommandRunner& cmdRunner, int lba, int testSize, const vector<string>& data) const
{
	int totalResult = true;
	for (int i = 0; i < testSize; i++) {
		if (WRITESUCCESS == cmdRunner.write(std::to_string(lba + i), data[i]))
			continue;
		totalResult = false;
	}

	return totalResult;
}

bool FullWriteAndReadCompareCommand::partialReadAndCompare(const CommandRunner& cmdRunner, int lba, int testSize, const vector<string>& data) const
{
	int totalResult = true;
	for (int i = 0; i < testSize; i++) {
		if (data[i] == cmdRunner.read(std::to_string(lba + i)))
			continue;
		totalResult = false;
	}

	return totalResult;
}

vector<string> FullWriteAndReadCompareCommand::getTestData(int testsize, int random) const
{
#ifdef _DEBUG
	random = 0;
#endif

	vector<string> data;
	RandomNumberGenerator rng;
	string testData = MAGICVALUE;
	
	if (random)
		testData = rng.generateRandomUnsignedIntString();

	for (int i = 0; i < testsize; i++) {
			data.push_back(testData);
	}

	return data;
}

std::shared_ptr<Command> FullWriteAndReadCompareCommandFactory::makeCommand(const string& cmdName
																			, const std::vector<string>& args)
{
	if (cmdName != CMD_1_FULL_WRITE_AND_READ_COMPARE) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<FullWriteAndReadCompareCommand>(new FullWriteAndReadCompareCommand(args));
}
