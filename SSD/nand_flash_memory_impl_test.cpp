#include "gmock/gmock.h"
#include "nand_flash_memory_impl.h"
#include "file_handler_mock.h"
#include <vector>
#include <string>

using namespace testing;
using std::vector;

TEST(NandFlashMemoryImpl, readTest) {
	FileHandlerMock mockedFileHandler;
	NandFlashMemoryImpl memory{ &mockedFileHandler };

	vector<string> writtenDatas = { "0\t0x00000000","1\t0x00000001" };
	EXPECT_CALL(mockedFileHandler, read("ssd_nand.txt")).WillRepeatedly(Return(writtenDatas));
	vector<string> expected = { "0x00000000", "0x00000001" };
	vector<string> actual = memory.read();

	EXPECT_EQ(expected, actual);
}

TEST(NandFlashMemoryImpl, writeTest) {
	FileHandlerMock mockedFileHandler;
	NandFlashMemoryImpl memory{ &mockedFileHandler };

	vector<string> writingDatas = { "0\t0x00000000","1\t0x00000001" };
	EXPECT_CALL(mockedFileHandler, write("ssd_nand.txt",writingDatas)).Times(1);
	vector<string> writingData = { "0x00000000", "0x00000001" };
	string actual = memory.write(writingData);

	EXPECT_EQ("", actual);
}