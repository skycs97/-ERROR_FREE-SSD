#include "gmock/gmock.h"
#include "OutputHandler.h"
#include "file_handler_mock.h"

using namespace testing;

TEST(Output, mock_file_test) {
	NiceMock<FileHandlerMock> fhMock;
	OutputHandler oh(&fhMock);

	EXPECT_CALL(fhMock, write(OUTPUT_FILENAME, _))
		.Times(1);

	oh.output("ERROR");
}
