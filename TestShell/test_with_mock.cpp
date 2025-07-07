#include "gmock/gmock.h"
#include "storage.h"
#include <string>

using std::string;
using namespace testing;

class MockStorage : public Storage {
public:
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(string, write, (int, int), (override));
};


TEST(TestShell, ReadMock) {
	int LBA = 30;
	string expected = "0x12341234";

	MockStorage storage;
	EXPECT_CALL(storage, read)
		.WillOnce(Return(expected));

	string actual = storage.read(LBA);

	EXPECT_EQ(expected, actual);
}

TEST(TestShell, ReadFailMock) {
	int LBA = 100;
	string expected = "ERROR";

	MockStorage storage;
	EXPECT_CALL(storage, read)
		.WillOnce(Return(expected));

	string actual = storage.read(LBA);

	EXPECT_EQ(expected, actual);
}

TEST(SSD, WriteExceedIndex) {
	MockStorage mock;

	string expected = "ERROR";
	EXPECT_CALL(mock, write(Ge(100), _))
		.WillRepeatedly(Return("ERROR"));
	EXPECT_CALL(mock, write(Le(-1), _))
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ(string(expected), string(mock.write(100, 0xFFFF)));
	EXPECT_EQ(string(expected), string(mock.write(-1, 0xFFFF)));
}

TEST(SSD, WriteSuccess) {
	MockStorage mock;

	string expected = "";
	EXPECT_CALL(mock, write(Le(99), _))
		.WillRepeatedly(Return(""));

	EXPECT_EQ(string(expected), string(mock.write(4, 0xFFFF)));
}
