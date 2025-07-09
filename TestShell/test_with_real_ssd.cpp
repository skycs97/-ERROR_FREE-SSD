#include "gmock/gmock.h"
#include "ssd_interface.h"
#include <string>
#include "command_runner.h"
#include "command.h"

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

TEST_F(TestShellFixtureWithReal, CmdRunnerRealRead) {
	SetUp();

	EXPECT_EQ("", runner.write(VALID_LBA, ERASE_VALUE));
	EXPECT_EQ(ERASE_VALUE, runner.read(VALID_LBA));

}

TEST_F(TestShellFixtureWithReal, CmdRunnerRealRead2) {
	SetUp();

	EXPECT_EQ("", runner.write(VALID_LBA, TEST_VALUE));
	EXPECT_EQ(TEST_VALUE, runner.read(VALID_LBA));
}

TEST_F(TestShellFixtureWithReal, CmdRunnerRealWriteError) {
	SetUp();

	EXPECT_EQ(ERROR_STRING, runner.write(INVALID_LBA, TEST_VALUE));
}