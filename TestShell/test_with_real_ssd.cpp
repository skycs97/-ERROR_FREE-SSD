#include "gmock/gmock.h"
#include "ssd_interface.h"
#include <string>
#include "command_runner.h"
#include "command_list.h"
#include "command_factory.h"
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
	FactoryCommand fc;

	const string VALID_LBA = "10";
	const string INVALID_LBA = "1000";
	const string TEST_VALUE = "0xAAAABBBB";
	const string ERASE_VALUE = "0x00000000";
	const string ERROR_STRING = "ERROR";
	static const int MIN_LBA = 0;
	static const int MAX_LBA = 99;
};

TEST_F(TestShellFixtureWithReal, CmdRunnerRealReadSuccess) {
	Command* writeCommand = fc.makeCommand("write " + VALID_LBA+" "+ TEST_VALUE);
	EXPECT_TRUE(writeCommand != nullptr);

	writeCommand->run(runner);

	Command* readCommand = fc.makeCommand("read " + VALID_LBA);	
	EXPECT_TRUE(readCommand != nullptr);

	readCommand->run(runner);
}

TEST_F(TestShellFixtureWithReal, CmdRunnerRealReadFail) {
	Command* writeCommand = fc.makeCommand("write " + INVALID_LBA + " " + TEST_VALUE);
	EXPECT_TRUE(writeCommand != nullptr);

	writeCommand->run(runner);

	Command* readCommand = fc.makeCommand("read " + INVALID_LBA);
	EXPECT_TRUE(readCommand != nullptr);

	readCommand->run(runner);
}
