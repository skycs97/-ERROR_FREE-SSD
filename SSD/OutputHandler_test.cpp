#include "gmock/gmock.h"
#include "OutputHandler.h"

class OutputHandlerMock : public OutputHandler {
public:
	//virtual unsigned char read(long address) = 0;
	//virtual void write(long address, unsigned char data) = 0;

	MOCK_METHOD(void, output, (const string&), (override));
};


TEST(Output, mock_output_test) {
	OutputHandlerMock oh;

	EXPECT_CALL(oh, output)
		.Times(1);

	oh.output("ERROR");
}
