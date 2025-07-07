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

TEST(SSD, WriteExccedIndex) {
	MockStroage mock;

	string expected = "ERROR";
	EXPECT_CALL(mock, write(Gt(99), _))
		.WillRepeatedly(Return("ERROR"));

	EXPECT_EQ(string(expected), string(mock.write(100, 0xFFFF)));
}