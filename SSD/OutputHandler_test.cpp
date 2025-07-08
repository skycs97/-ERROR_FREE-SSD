#include "gmock/gmock.h"
#include "OutputHandler.h"
#include "FileHandler.h"

using namespace testing;

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(void, write, (const std::string&, const std::vector<string> &), (override));
	MOCK_METHOD(std::string, read, (const std::string&), (override));
};

TEST(Output, mock_file_test) {
	NiceMock<FileHandlerMock> fhMock;
	OutputHandler oh(&fhMock);
	const string OUTPUT_FILENAME = "ssd_output.txt";
	EXPECT_CALL(fhMock, write({ "ssd_output.txt", _))
		.Times(1);

	oh.output("ERROR");
}
