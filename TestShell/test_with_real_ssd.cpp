#ifdef _DEBUG
#include "gmock/gmock.h"
#include "ssd_interface.h"
#include <string>
#include "command_runner.h"
#include "command_list.h"
#include "command_parser.h"
#include "ssd_impl.h"

using std::string;
using namespace testing;

class TestShellFixtureWithReal : public Test {
protected:
	void SetUp() {
		runner.setStorage(&storage);
	}

public:
	SsdImpl storage;
	CommandRunner runner;
	CommandParser parser;
	const string VALID_LBA = "10";
	const string INVALID_LBA = "1000";
	const string TEST_VALUE = "0xAAAABBBB";
	const string ERASE_VALUE = "0x00000000";
	const string ERROR_STRING = "ERROR";
	static const int MIN_LBA = 0;
	static const int MAX_LBA = 99;
};

TEST_F(TestShellFixtureWithReal, CmdRunnerRealReadSuccess) {
	auto writeCommand = parser.parseAndMakeShellCommand("write " + VALID_LBA+" "+ TEST_VALUE);
	EXPECT_TRUE(writeCommand != nullptr);

	writeCommand->run(runner);

	auto readCommand = parser.parseAndMakeShellCommand("read " + VALID_LBA);
	EXPECT_TRUE(readCommand != nullptr);

	readCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, CmdRunnerRealReadFail) {
	auto writeCommand = parser.parseAndMakeShellCommand("write " + INVALID_LBA + " " + TEST_VALUE);
	EXPECT_TRUE(writeCommand != nullptr);

	writeCommand->run(runner);

	auto readCommand = parser.parseAndMakeShellCommand("read " + INVALID_LBA);
	EXPECT_TRUE(readCommand != nullptr);

	readCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, Erase) {
	const string startIdx = "0";
	const string range = "10";
	auto eraseCommand = parser.parseAndMakeShellCommand("erase " + startIdx + " " + range);
	EXPECT_TRUE(eraseCommand != nullptr); 

	eraseCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, EraseInRange) {
	const string startIdx = "0";
	const string endIdx = "10";

	auto eraseCommand = parser.parseAndMakeShellCommand("erase_range " + startIdx + " " + endIdx);
	EXPECT_TRUE(eraseCommand != nullptr);

	eraseCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, CmdRunnerFlush) {
	auto writeCommand = parser.parseAndMakeShellCommand("flush");
	EXPECT_TRUE(writeCommand != nullptr);

	writeCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, FullWriteAndReadCompare) {
	auto fullWriteAndReadCompareCommand = parser.parseAndMakeShellCommand("1_");
	EXPECT_TRUE(fullWriteAndReadCompareCommand != nullptr);

	fullWriteAndReadCompareCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, PartialLBAWrite) {
	auto partialLBAWriteCommand = parser.parseAndMakeShellCommand("2_");
	EXPECT_TRUE(partialLBAWriteCommand != nullptr);

	partialLBAWriteCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, WriteReadAging) {
	auto writeReadAgingCommand = parser.parseAndMakeShellCommand("3_");
	EXPECT_TRUE(writeReadAgingCommand != nullptr);

	writeReadAgingCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, EraseAndWriteAging) {
	auto eraseAndWriteAgingCommand = parser.parseAndMakeShellCommand("4_");
	EXPECT_TRUE(eraseAndWriteAgingCommand != nullptr);

	eraseAndWriteAgingCommand->run(runner);
}

#endif