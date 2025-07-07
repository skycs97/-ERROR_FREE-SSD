#include "gmock/gmock.h"
#include "nand_reader.h"
#include "nand_flash_memory_mock.h"

using namespace testing;

TEST(NandReader, readTestWithSuccessResult) {
	NandFlashMemoryMock memory;
	NandReader nand_reader(&memory);
	EXPECT_CALL(memory, read(_)).WillRepeatedly(Return(0x12345678));
	int lba = 10;
	int actual = nand_reader.read(lba);
	int expected = 0x12345678;
	EXPECT_EQ(expected, actual);
};