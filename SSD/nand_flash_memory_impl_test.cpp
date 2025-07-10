#define _CRT_SECURE_NO_WARNINGS
#include "gmock/gmock.h"
#include "nand_flash_memory_impl.h"
#include "file_handler_mock.h"
#include <vector>
#include <string>

using namespace testing;
using std::vector;

class NandFlashMemoryImplFixture : public Test {
public:
	char* createMockNandData(int lba, string data) {
		std::ostringstream oss;
		for (int i = MIN_LBA; i <= MAX_LBA; i++) {
			if (lba == i)
			{
				while (!data.empty() && (data.back() == '\n' || data.back() == '\r')) {
					data.pop_back();
				}
				oss << std::setfill('0') << std::setw(2) << std::dec << i << '\t'
					<< std::setfill('0') << std::setw(8) << std::hex << std::uppercase << data
					<< '\n';
			}
			else
			{
				oss << std::setw(2) << std::setfill('0') << std::dec << i << '\t'
					<< "0x" << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << 0
					<< '\n';
			}
		}

		std::string str = oss.str();

		// 동적 메모리 할당 (null-terminated)
		char* nandData = new char[str.size() + 1];
		std::strcpy(nandData, str.c_str());

		return nandData;
	}

	vector<string> convertToVectorStringFormat(const char* data) {
		vector<string> lines;
		std::istringstream iss(data);
		string line;

		while (std::getline(iss, line)) {
			lines.push_back(line.substr(line.find('\t') + 1));
		}

		return lines;
	}

	const char* VALID_WRITE_VALUE = "0x12341234";

	FileHandlerMock mockedFileHandler;
	NandFlashMemoryImpl memory{ &mockedFileHandler };
	char* nandData{ nullptr };
};

TEST_F(NandFlashMemoryImplFixture, readTest) {
	nandData = createMockNandData(0, VALID_WRITE_VALUE);
	vector<string> expected = convertToVectorStringFormat(nandData);

	EXPECT_CALL(mockedFileHandler, readFile(NAND_FILENAME))
		.WillRepeatedly(Return(nandData));

	vector<string> actual = memory.read();
	EXPECT_EQ(expected, actual);
}

TEST_F(NandFlashMemoryImplFixture, writeTest) {
	nandData = createMockNandData(0, VALID_WRITE_VALUE);
	vector<string> writingDatas = convertToVectorStringFormat(nandData);

	EXPECT_CALL(mockedFileHandler, writeData(NAND_FILENAME, nandData))
		.Times(1);

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
	nandData = createMockNandData(0, NAND_DATA_EMPTY);

	EXPECT_CALL(mockedFileHandler, isFileExistByMatchLength(_, _, _))
		.Times(1)
		.WillOnce(Return(false));

	EXPECT_CALL(mockedFileHandler, createFile(NAND_FILENAME))
		.Times(1);

	EXPECT_CALL(mockedFileHandler, writeData(NAND_FILENAME, nandData))
		.Times(1);

	memory.init();
}