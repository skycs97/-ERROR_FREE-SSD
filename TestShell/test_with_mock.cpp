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

