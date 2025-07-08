#include "gmock/gmock.h"
#include "nand_writer.h"
#include "nand_flash_memory_mock.h"

using namespace testing;

static const int VALID_RANGE_LBA = 53;
static const int INVALID_RANGE_LBA = 999;
static const string VALID_DATA = "0xAAAABBBB";

TEST(Writer, ValidCase)
{
	// arrange
	NandFlashMemoryMock nand;
	NandWriter writer(&nand);

	// act, assert
	EXPECT_CALL(nand, write(_))
		.WillRepeatedly(Return(""));

	string expected = "";
	string actual = writer.write(VALID_RANGE_LBA, VALID_DATA);
	EXPECT_EQ(expected, actual);
}

TEST(Writer, InvalidCase_OutOfRange)
{
	// arrange
	NandFlashMemoryMock nand;
	NandWriter writer(&nand);

	// act, assert
	EXPECT_CALL(nand, write(_))
		.Times(0);

	string expected = "ERROR";
	string actual = writer.write(INVALID_RANGE_LBA, VALID_DATA);
	EXPECT_EQ(expected, actual);
}