#include "gmock/gmock.h"
using namespace testing;

TEST(NandReader, read) {
	NandFlashMemory* memory = new NandFlashMemoryMock();
	NandReader nand_reader(memory);
	EXPECT_CALL(flash, read(_)).CallRepeatedly(Return(0x12345678));
	int lba = 10;
	int actual = nand_reader.read(lba);
	int expected = 0x12345678;
	EXPECT_EQ(expected, actual);
}