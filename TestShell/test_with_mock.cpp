#include "gmock/gmock.h"
#include "ssd_interface.h"
#include <string>
#include "command_runner.h"

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
};

TEST_F(TestShellFixtureWithMock, CmdRunnerRead) {
	string LBA = "10";

	EXPECT_CALL(mockStorage, read)
		.Times(1)
		.WillRepeatedly(Return("0x0000FFFF"));
	
	EXPECT_EQ("0x0000FFFF", runner.read(LBA));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerWrite) {
	string LBA = "10";
	string value = "0xAAAABBBB";
	EXPECT_CALL(mockStorage, write(LBA, _))
		.Times(1)
		.WillRepeatedly(Return(value));

	EXPECT_EQ(value, runner.write(LBA, value));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerReadFail) {
	string LBA = "1000";

	EXPECT_CALL(mockStorage, read)
		.Times(1)
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ("ERROR", runner.read(LBA));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerWriteFail) {
	string LBA = "1000";
	string value = "0xFFFFFFFF";

	EXPECT_CALL(mockStorage, write(LBA, _))
		.Times(1)
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ("ERROR", runner.write(LBA, value));
}

TEST_F(TestShellFixtureWithMock, CmdRunnerNoSetInterface) {
	CommandRunner emptyRunner;
	string LBA = "10";

	EXPECT_THROW(emptyRunner.read(LBA), std::runtime_error);
}