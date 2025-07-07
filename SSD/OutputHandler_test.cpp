#include "gmock/gmock.h"
#include "OutputHandler.h"
#include "FileHandler.h"

using namespace testing;

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(void, write, (const std::string&), (override));
	MOCK_METHOD(std::string, read, (), (override));
};

TEST(Output, mock_file_test) {
	NiceMock<FileHandlerMock> fhMock;
	OutputHandler oh(&fhMock);

	EXPECT_CALL(fhMock, write)
		.Times(1);

	EXPECT_CALL(fhMock, read)
		.WillRepeatedly(testing::Return("ERROR"));

	oh.output("ERROR");
	string readString = oh.read();

	EXPECT_EQ("ERROR", readString);
}
