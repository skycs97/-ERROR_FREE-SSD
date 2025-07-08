#include "gmock/gmock.h"
#include "ssd_interface.h"
#include <string>
#include "command_runner.h"

using std::string;
using namespace testing;

class SsdInterfaceMock : public SsdInterface {
public:
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(string, write, (int, int), (override));
};

class TestShellFixtureWithMock : public Test {
protected:
	void SetUp() {
		runner.setStorage(&mockStorage);
	}
public:
	SsdInterfaceMock mockStorage;
	CommandRunner runner;
};

TEST_F(TestShellFixtureWithMock, CmdRunnerRead) {
	vector<string> command = { "\SSD.exe", "R", "1" };

	EXPECT_CALL(mockStorage, read)
		.Times(1)
		.WillRepeatedly(Return("0x0000FFFF"));
	
	EXPECT_EQ("0x0000FFFF", runner.runCommand(command));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerWrite) {
	vector<string> command = { "\SSD.exe", "W", "2", "0xAAAABBBB"};

	EXPECT_CALL(mockStorage, write)
		.Times(1)
		.WillRepeatedly(Return(""));

	EXPECT_EQ("", runner.runCommand(command));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerReadFail) {
	vector<string> command = { "\SSD.exe", "R", "110" };

	EXPECT_CALL(mockStorage, read)
		.Times(1)
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ("ERROR", runner.runCommand(command));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerWriteFail) {
	vector<string> command = { "\SSD.exe", "W", "110", "0xFFFFFFFF"};

	EXPECT_CALL(mockStorage, write)
		.Times(1)
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ("ERROR", runner.runCommand(command));
}