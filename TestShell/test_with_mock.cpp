#include "gmock/gmock.h"
#include "stroage.h"
#include <string>

using std::string;
using namespace testing;

class MockStroage : public Stroage {
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(string, write, (int, int), (override);
};

