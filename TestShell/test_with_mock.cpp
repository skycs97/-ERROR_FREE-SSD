#include "gmock/gmock.h"
#include "storage.h"
#include <string>
#include "command_runner.h"

using std::string;
using namespace testing;

class MockStorage : public Storage {
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
	MockStorage mockStorage;
	CommandRunner runner;
	
};

TEST_F(TestShellFixtureWithMock, ReadMock) {
	int LBA = 99;
	string expected = "0xFFFFFFFF";
	EXPECT_CALL(mockStorage, read)
		.WillOnce(Return(expected));

	string actual = mockStorage.read(LBA);

	EXPECT_EQ(expected, actual);
}

TEST_F(TestShellFixtureWithMock, ReadFailMock) {
	int LBA = 100;
	string expected = "ERROR";
	EXPECT_CALL(mockStorage, read)
		.WillOnce(Return(expected));

	string actual = mockStorage.read(LBA);

	EXPECT_EQ(expected, actual);
}

TEST_F(TestShellFixtureWithMock, WriteExceedIndex) {
	string expected = "ERROR";
	EXPECT_CALL(mockStorage, write(Ge(100), _))
		.WillRepeatedly(Return("ERROR"));
	EXPECT_CALL(mockStorage, write(Le(-1), _))
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ(string(expected), string(mockStorage.write(100, 0xFFFF)));
	EXPECT_EQ(string(expected), string(mockStorage.write(-1, 0xFFFF)));
}

TEST_F(TestShellFixtureWithMock, WriteSuccess) {
	string expected = "";
	EXPECT_CALL(mockStorage, write(Le(99), _))
		.WillRepeatedly(Return(""));

	EXPECT_EQ(string(expected), string(mockStorage.write(4, 0xFFFF)));
}

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