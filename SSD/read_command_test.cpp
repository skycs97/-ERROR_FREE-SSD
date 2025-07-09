#include "gmock/gmock.h"
#include "read_command.h"
#include "nand_flash_memory_mock.h"
#include "file_handler_mock.h"
using std::string;
using namespace testing;

class ReadCommandFixture : public Test {
public:
	static constexpr int LBA_IN_RANGE = 0;
	const vector<string> NAND_WRITTEN_VALUE = { "0x12345678" };

	FileHandlerMock mockedFileHandler;
	NandFlashMemoryMock memory;
	BufferManager bufferManager{ &memory, &mockedFileHandler };
	ReadCommand readCommand{ &memory , &bufferManager};
};

TEST_F(ReadCommandFixture, readTestWithSuccessResult) {
	EXPECT_CALL(memory, read()).WillRepeatedly(Return(NAND_WRITTEN_VALUE));
	string actual = readCommand.read(LBA_IN_RANGE);
	string expected = "0x12345678";

	EXPECT_EQ(expected, actual);
};