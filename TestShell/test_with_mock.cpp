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

TEST(SSD, WriteExceedIndex) {
	MockStroage mock;

	string expected = "ERROR";
	EXPECT_CALL(mock, write(Ge(100), _))
		.WillRepeatedly(Return("ERROR"));
	EXPECT_CALL(mock, write(Le(-1), _))
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ(string(expected), string(mock.write(100, 0xFFFF)));
	EXPECT_EQ(string(expected), string(mock.write(-1, 0xFFFF)));
}

TEST(SSD, WriteSuccess) {
	MockStroage mock;

	string expected = "";
	EXPECT_CALL(mock, write(Le(99), _))
		.WillRepeatedly(Return(""));

	EXPECT_EQ(string(expected), string(mock.write(4, 0xFFFF)));
}
