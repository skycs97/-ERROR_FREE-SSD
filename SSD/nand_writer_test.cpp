#include "gmock/gmock.h"
#include "writer.h"
#include "nand_flash_memory_mock.h"

using namespace testing;

TEST(Writer, WriteZeroInLBA0)
{
	// arrange
	NandFlashMemoryMock memory;
	NandWriter writer;

	// act, assert
	EXPECT_CALL(memory, write(_, _))
		.WillRepeatedly(Return(0x00000000));

	int lba = 0;
	int data = 0x00000000;
	string expected = "";
	string actual = writer.write(lba, data);
	EXPECT_EQ(expected, actual);
}