#include "gmock/gmock.h"
#include "nand_reader.h"
#include "nand_flash_memory_mock.h"

using namespace testing;
static constexpr int LBA_IN_RANGE = 10;
static constexpr int LBA_OUT_RANGE = 105;
static constexpr int NAND_WRITTEN_VALUE = 0x12345678;

class NandReaderFixture : public Test {
public:
	NandFlashMemoryMock memory;
	NandReader nand_reader{ &memory };
};

TEST_F(NandReaderFixture, readTestWithSuccessResult) {
	EXPECT_CALL(memory, read(_)).WillRepeatedly(Return(NAND_WRITTEN_VALUE));
	int actual = nand_reader.read(LBA_IN_RANGE);
	int expected = NAND_WRITTEN_VALUE;

	EXPECT_EQ(expected, actual);
};

TEST_F(NandReaderFixture, readTestWithOutRangedLBA) {
	EXPECT_THROW(nand_reader.read(LBA_OUT_RANGE), std::runtime_error);
};