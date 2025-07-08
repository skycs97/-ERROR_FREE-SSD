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

	vector<string> expectingWriteDatas;
	for (int i = 0; i < 100; i++) {
		std::ostringstream oss;
		oss << i << '\t' << "0x00001111";
		expectingWriteDatas.push_back(oss.str());
	}
	vector<string> writingDatas;
	for (int i = 0; i < 100; i++) {
		writingDatas.push_back("0x00001111");
	}
	EXPECT_CALL(mockedFileHandler, write("ssd_nand.txt", expectingWriteDatas)).Times(1);
	string actual = memory.write(writingDatas);

	EXPECT_EQ("", actual);
}