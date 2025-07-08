#include "gmock/gmock.h"
#include "ssd_interface.h"
#include <string>
#include "command_runner.h"
#include "command.h"

using std::string;
using namespace testing;

class SsdInterfaceMock : public SsdInterface {
public:
	MOCK_METHOD(string, read, (const string&), (override));
	MOCK_METHOD(string, write, (const string&, const string&), (override));
};

class TestShellFixtureWithMock : public Test {
protected:
	void SetUp() {
		runner.setStorage(&mockStorage);
	}
public:
	SsdInterfaceMock mockStorage;
	CommandRunner runner;
	FactoryCommand fc;

	const string VALID_LBA = "10";
	const string INVALID_LBA = "1000";
	const string TEST_VALUE = "0xAAAABBBB";
	const string ERROR_STRING = "ERROR";
};

TEST_F(TestShellFixtureWithMock, CmdRunnerRead) {
	EXPECT_CALL(mockStorage, read(VALID_LBA))
		.Times(1)
		.WillRepeatedly(Return("0x0000FFFF"));

	EXPECT_EQ("0x0000FFFF", runner.read(VALID_LBA));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerWrite) {
	EXPECT_CALL(mockStorage, write(VALID_LBA, _))
		.Times(1)
		.WillRepeatedly(Return(TEST_VALUE));

	EXPECT_EQ(TEST_VALUE, runner.write(VALID_LBA, TEST_VALUE));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerReadFail) {
	EXPECT_CALL(mockStorage, read(INVALID_LBA))
		.Times(1)
		.WillRepeatedly(Return(ERROR_STRING));

	EXPECT_EQ(ERROR_STRING, runner.read(INVALID_LBA));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerWriteFail) {
	EXPECT_CALL(mockStorage, write(INVALID_LBA, _))
		.Times(1)
		.WillRepeatedly(Return(ERROR_STRING));

	EXPECT_EQ(ERROR_STRING, runner.write(INVALID_LBA, TEST_VALUE));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerNoSetInterface) {
	CommandRunner emptyRunner;

	EXPECT_THROW(emptyRunner.read(VALID_LBA), std::runtime_error);
}
TEST_F(TestShellFixtureWithMock, CommandRunRead) {

	Command* command = fc.makeCommand("read " + VALID_LBA);

	EXPECT_CALL(mockStorage, read(VALID_LBA))
		.Times(1);
	EXPECT_TRUE(command != nullptr);

	command->run(runner);
}

TEST_F(TestShellFixtureWithMock, CommandRunWrite) {

	Command* command = fc.makeCommand("write " + VALID_LBA + " " + TEST_VALUE);

	EXPECT_CALL(mockStorage, write(VALID_LBA, _))
		.Times(1);
	EXPECT_TRUE(command != nullptr);

	command->run(runner);
}

TEST_F(TestShellFixtureWithMock, CommandRunFullRead) {

	Command* command = fc.makeCommand("fullread");

	EXPECT_CALL(mockStorage, read(_))
		.Times(100);
	EXPECT_TRUE(command != nullptr);

	command->run(runner);
}

TEST_F(TestShellFixtureWithMock, CommandRunFullWrite) {

	Command* command = fc.makeCommand("fullwrite " + TEST_VALUE);

	EXPECT_CALL(mockStorage, write(_, _))
		.Times(100);
	EXPECT_TRUE(command != nullptr);

	command->run(runner);
}

TEST_F(TestShellFixtureWithMock, CommandRunFullWriteAndReadCompare) {
	Command* command = fc.makeCommand("1_ ");

	EXPECT_CALL(mockStorage, read(_))
		.Times(100)
		.WillRepeatedly(Return("0xA5A5A5A5"));

	EXPECT_CALL(mockStorage, write(_, _))
		.Times(100)
		.WillRepeatedly(Return(""));

	command->run(runner);
}