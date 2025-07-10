#include "gmock/gmock.h"
#include "write_command.h"
#include "nand_flash_memory_mock.h"
#include "file_handler_mock.h"

using namespace testing;

class WriteCommandFixture : public Test
{
public:
	static constexpr int ARGC = 4;
	const char* VALID_LBA = "53";
	const char* VALID_DATA = "0xAAAABBBB";
	const char* INIT_DATA = "0x00000000";
	const char* VALID_ARGV[ARGC] = { "ssd.exe", "W", VALID_LBA, VALID_DATA };

	NiceMock<FileHandlerMock> mockedFileHandler;
	NandFlashMemoryMock nand;
	BufferManager bufferManager{ &nand, &mockedFileHandler };
	WriteCommand writeCommand{ &nand, &bufferManager };
	vector<string> dummy_data{ MAX_LBA, INIT_DATA };
};

#if BUFFER_ENABLE == false
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
	writeCommand.parseArg(ARGC, VALID_ARGV);
	string actual = writeCommand.run();
	EXPECT_EQ(expected, actual);
}
#else
TEST_F(WriteCommandFixture, ValidCase)
{
	// act, assert
	EXPECT_CALL(nand, read())
		.Times(0);

	EXPECT_CALL(nand, write(_))
		.Times(0);

	string expected = "";
	writeCommand.parseArg(ARGC, VALID_ARGV);
	string actual = writeCommand.run();
	EXPECT_EQ(expected, actual);
}
#endif