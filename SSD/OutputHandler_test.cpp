#include "gmock/gmock.h"
#include "OutputHandler.h"
#include "FileHandler.h"

using namespace testing;

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(void, write, (const string&, const vector<string>&), (override));
};

TEST(Output, mock_file_test) {
	NiceMock<FileHandlerMock> fhMock;
	OutputHandler oh(&fhMock);
	const string OUTPUT_FILENAME = "ssd_output.txt";
	EXPECT_CALL(fhMock, write(OUTPUT_FILENAME, _))
		.Times(1);

	oh.output("ERROR");
}
