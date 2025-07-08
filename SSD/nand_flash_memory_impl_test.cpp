#include "gmock/gmock.h"
#include "nand_flash_memory_impl.h"
#include "file_handler_mock.h"
#include <vector>
#include <string>

using namespace testing;
using std::vector;

class NandFlashMemoryImplFixture : public Test {
public:
	vector<string> GetFullSameDataWithLBA(string data)
	{
		vector<string> expectingWriteDatas;
		for (int i = MIN_LBA; i <= MAX_LBA; i++) {
			std::ostringstream oss;
			oss << i << '\t' << data;
			expectingWriteDatas.push_back(oss.str());
		}
		return expectingWriteDatas;
	}

	vector<string> GetFullSameDataWihtoutLBA(string data)
	{
		vector<string> writingDatas;
		for (int i = MIN_LBA; i <= MAX_LBA; i++) {
			writingDatas.push_back(data);
		}
		return writingDatas;
	}

	FileHandlerMock mockedFileHandler;
	NandFlashMemoryImpl memory{ &mockedFileHandler };
};

TEST_F(NandFlashMemoryImplFixture, readTest) {
	vector<string> writtenDatas = { "0\t0x00000000","1\t0x00000001" };
	EXPECT_CALL(mockedFileHandler, read("ssd_nand.txt")).WillRepeatedly(Return(writtenDatas));
	vector<string> expected = { "0x00000000", "0x00000001" };
	vector<string> actual = memory.read();

	EXPECT_EQ(expected, actual);
}

TEST_F(NandFlashMemoryImplFixture, writeTest) {
	vector<string> expectingWriteDatas = GetFullSameDataWithLBA("0x00001111");
	vector<string> writingDatas = GetFullSameDataWihtoutLBA("0x00001111");
	
	EXPECT_CALL(mockedFileHandler, write(NAND_FILENAME, expectingWriteDatas)).Times(1);
	string actual = memory.write(writingDatas);

	EXPECT_EQ("", actual);
}

TEST_F(NandFlashMemoryImplFixture, NandFile_Exist) {
	EXPECT_CALL(mockedFileHandler, checkExistNandFile)
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(mockedFileHandler, createInitNandFile)
		.Times(0);

	mockedFileHandler.init();
}

TEST_F(NandFlashMemoryImplFixture, NandFile_NoExist) {
	EXPECT_CALL(mockedFileHandler, checkExistNandFile)
		.Times(1)
		.WillOnce(Return(false));
	EXPECT_CALL(mockedFileHandler, createInitNandFile)
		.Times(1);

	mockedFileHandler.init();
}