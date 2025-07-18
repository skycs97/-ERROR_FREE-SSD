#include "gmock/gmock.h"
#include "output_handler.h"
#include "file_handler_mock.h"

using namespace testing;

TEST(Output, mock_file_test) {
	NiceMock<FileHandlerMock> fhMock;
	OutputHandler oh(&fhMock);

	EXPECT_CALL(fhMock, writeData(OUTPUT_FILENAME, _))
		.Times(1);

	oh.output("ERROR");
}
