#include "gmock/gmock.h"
#include "nand_reader.h"
#include "nand_flash_memory_mock.h"
using std::string;
using namespace testing;

class NandReaderFixture : public Test {
public:
	static constexpr int LBA_IN_RANGE = 0;
	static constexpr int LBA_OVER_99 = 105;
	static constexpr int LBA_UNDER_0 = -1;
	const vector<string> NAND_WRITTEN_VALUE = { "0x12345678" };

	NandFlashMemoryMock memory;
	NandReader nand_reader{ &memory };
};

TEST_F(NandReaderFixture, readTestWithSuccessResult) {
	EXPECT_CALL(memory, read()).WillRepeatedly(Return(NAND_WRITTEN_VALUE));
	string actual = nand_reader.read(LBA_IN_RANGE);
	string expected = "0x12345678";

	EXPECT_EQ(expected, actual);
};

TEST_F(NandReaderFixture, readTestWithOutRangedLBA) {
	EXPECT_THROW(nand_reader.read(LBA_OVER_99), std::runtime_error);
	EXPECT_THROW(nand_reader.read(LBA_UNDER_0), std::runtime_error);
};