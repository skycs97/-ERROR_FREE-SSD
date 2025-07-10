#include "gmock/gmock.h"
#include "nand_flash_memory_impl.h"
#include "file_handler_mock.h"
#include <vector>
#include <string>

using namespace testing;
using std::vector;

class NandFlashMemoryImplFixture : public Test {
public:
	string GetFullSameDataWithLBA(string data)
	{
		std::ostringstream oss;
		for (int i = MIN_LBA; i <= MAX_LBA; ++i) {
			oss << std::setfill('0') << std::setw(2) << std::dec << i << '\t'
				<< data << "\n";
		}
		return oss.str();
	}

	vector<string> GetFullSameDataWithoutLBA(string data)
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
	string formattedData = GetFullSameDataWithLBA("0x00001111");
	vector<string> writingDatas = GetFullSameDataWithoutLBA("0x00001111");
	
	EXPECT_CALL(mockedFileHandler, writeData(NAND_FILENAME, formattedData)).Times(1);
	string actual = memory.write(writingDatas);

	EXPECT_EQ("", actual);
}

TEST_F(NandFlashMemoryImplFixture, NandFile_Exist) {
	EXPECT_CALL(mockedFileHandler, isFileExistByMatchLength(_, _, _))
		.Times(1)
		.WillOnce(Return(true));

	EXPECT_CALL(mockedFileHandler, createFile(_))
		.Times(0);

	EXPECT_CALL(mockedFileHandler, writeData(_, _))
		.Times(0);

	memory.init();
}

TEST_F(NandFlashMemoryImplFixture, NandFile_NoExist) {
	EXPECT_CALL(mockedFileHandler, isFileExistByMatchLength(_, _, _))
		.Times(1)
		.WillOnce(Return(false));

	EXPECT_CALL(mockedFileHandler, createFile(_))
		.Times(1);

	EXPECT_CALL(mockedFileHandler, writeData(_, _))
		.Times(1);

	memory.init();
}