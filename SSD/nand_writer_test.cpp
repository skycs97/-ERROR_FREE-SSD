#include "gmock/gmock.h"
#include "nand_writer.h"
#include "nand_flash_memory_mock.h"

using namespace testing;

TEST(Writer, WriteZeroInLBA0)
{
	// arrange
	NandFlashMemoryMock memory;
	NandWriter writer(&memory);

	// act, assert
	EXPECT_CALL(memory, write(_, _))
		.WillRepeatedly(Return(""));

	int lba = 0;
	int data = 0x00000000;
	string expected = "";
	string actual = writer.write(lba, data);
	EXPECT_EQ(expected, actual);
}