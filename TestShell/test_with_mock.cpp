#include "gmock/gmock.h"
#include "storage.h"
#include <string>

using std::string;
using namespace testing;

class MockStroage : public Storage {
public:
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(string, write, (int, int), (override));
};



TEST(TestShell, ReadMock) {
	MockStroage storage;
	EXPECT_CALL(storage, read)
		.WillOnce(Return("0x12341234"));

	string actual = storage.read(30);

	EXPECT_EQ("0x12341234", actual);
}

TEST(TestShell, ReadFailMock) {
	MockStroage storage;
	EXPECT_CALL(storage, read)
		.WillOnce(Return("Error"));

	string actual = storage.read(100);

	EXPECT_EQ("Error", actual);
}