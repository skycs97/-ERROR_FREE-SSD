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