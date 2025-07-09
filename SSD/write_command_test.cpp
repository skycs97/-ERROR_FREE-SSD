#include "gmock/gmock.h"
#include "write_command.h"
#include "nand_flash_memory_mock.h"
#include "file_handler_mock.h"

using namespace testing;

static const int VALID_RANGE_LBA = 53;
static const string VALID_DATA = "0xAAAABBBB";
static const string INIT_DATA = "0x00000000";

class WriteCommandFixture : public Test
{
public:
	FileHandlerMock mockedFileHandler;
	NandFlashMemoryMock nand;
	BufferManager bufferManager{ &nand, &mockedFileHandler };
	WriteCommand writeCommand{ &nand, &bufferManager };
	vector<string> dummy_data{ MAX_LBA, INIT_DATA };
};

TEST_F(WriteCommandFixture, ValidCase)
{
	// act, assert
	EXPECT_CALL(nand, read())
		.Times(1)
		.WillOnce(Return(dummy_data));

	EXPECT_CALL(nand, write(_))
		.Times(1)
		.WillRepeatedly(Return(""));

	string expected = "";
	string actual = writeCommand.write(VALID_RANGE_LBA, VALID_DATA);
	EXPECT_EQ(expected, actual);
}