#include "gmock/gmock.h"
#include "nand_reader.h"
#include "nand_flash_memory_mock.h"
using std::string;
using namespace testing;

class NandReaderFixture : public Test {
public:
	static constexpr int LBA_IN_RANGE = 10;
	static constexpr int LBA_OUT_RANGE = 105;
	const string NAND_WRITTEN_VALUE = string{ "0x12345678" };

	NandFlashMemoryMock memory;
	NandReader nand_reader{ &memory };
};

TEST_F(NandReaderFixture, readTestWithSuccessResult) {
	EXPECT_CALL(memory, read(_)).WillRepeatedly(Return(NAND_WRITTEN_VALUE));
	string actual = nand_reader.read(LBA_IN_RANGE);
	string expected = NAND_WRITTEN_VALUE;

	EXPECT_EQ(expected, actual);
};

TEST_F(NandReaderFixture, readTestWithOutRangedLBA) {
	EXPECT_THROW(nand_reader.read(LBA_OUT_RANGE), std::runtime_error);
};