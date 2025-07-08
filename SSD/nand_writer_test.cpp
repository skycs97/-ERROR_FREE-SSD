#include "gmock/gmock.h"
#include "nand_writer.h"
#include "nand_flash_memory_mock.h"

using namespace testing;

static const int VALID_RANGE_LBA = 53;
static const string VALID_DATA = "0xAAAABBBB";
static const string INIT_DATA = "0x00000000";

class WriterFixture : public Test
{
public:
	NandFlashMemoryMock nand;
	NandWriter writer{ &nand };
	vector<string> dummy_data{ MAX_LBA, INIT_DATA };
};

TEST_F(WriterFixture, ValidCase)
{
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