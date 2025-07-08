#include "gmock/gmock.h"
#include "nand_writer.h"
#include "nand_flash_memory_mock.h"

using namespace testing;

static const int MAX_LBA = 100;
static const int VALID_RANGE_LBA = 53;
static const int INVALID_RANGE_LBA = 999;
static const string VALID_DATA = "0xAAAABBBB";
static const string INIT_DATA = "0x00000000";

TEST(Writer, ValidCase)
{
	// arrange
	NandFlashMemoryMock nand;
	NandWriter writer(&nand);
	vector<string> dummy_data(MAX_LBA, INIT_DATA);

	// act, assert
	EXPECT_CALL(nand, read())
		.Times(1)
		.WillOnce(Return(dummy_data));

	EXPECT_CALL(nand, write(_))
		.Times(1)
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