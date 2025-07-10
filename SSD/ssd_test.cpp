#define _CRT_SECURE_NO_WARNINGS
#include "gmock/gmock.h"
#include "ssd.h"
#include "file_handler_mock.h"

using namespace testing;

class SSDFixture : public Test {
protected:
	void SetUp() override {
		EXPECT_CALL(mockedFileHandler, isFileExistByMatchLength(_, _, _))
			.Times(1)
			.WillOnce(Return(true));

		EXPECT_CALL(mockedFileHandler, readFile(NAND_FILENAME))
			.WillRepeatedly(Return(nullptr));
	}
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

	const char* READ_ADDR = "1";
	const char* READ_SUCCESS = "0x00000001";
	const char* INVALID_READ_ADDR = "110";

	const char* WRITE_ADDR = "1";
	const char* VALID_WRITE_VALUE = "0x00001111";
	const char* VALID_NAND_DATA = "1\t0x00001111";
	const char* INVALID_WRITE_ADDR = "1";
	const char* INVALID_WRITE_VALUE = "0xzzzzFFFF";

	const char* READ_COMMAND = "r";
	const char* WRITE_COMMAND = "w";
	const char* WRITE_SUCCESS = "";
	const char* ERROR_MESSAGE = "ERROR";

	NiceMock<FileHandlerMock> mockedFileHandler;
	SSD ssd{ &mockedFileHandler };
	char* nandData;
};

TEST_F(SSDFixture, run_with_r_1)
{
	int argc = 3;
	const char* argv[] = { "ssd.exe", READ_COMMAND, READ_ADDR };
	nandData = createMockNandData(std::stoi(READ_ADDR), VALID_WRITE_VALUE);
	vector<string> expectedOutput = convertToVectorStringFormat(nandData);

	EXPECT_CALL(mockedFileHandler, readFile(NAND_FILENAME))
		.Times(1)
		.WillOnce(Return(nandData));

	EXPECT_CALL(mockedFileHandler, writeData(OUTPUT_FILENAME, VALID_WRITE_VALUE))
		.Times(1);

	ssd.run(argc, argv);
}

TEST_F(SSDFixture, run_with_r_110)
{
	int argc = 3;
	const char* argv[] = { "ssd.exe", READ_COMMAND, INVALID_READ_ADDR };

	EXPECT_CALL(mockedFileHandler, writeData(OUTPUT_FILENAME, ERROR_MESSAGE))
		.Times(1);

	ssd.run(argc, argv);
}

#if BUFFER_ENABLE == false
TEST_F(SSDFixture, run_with_w_1_0x00001111)
{
	int argc = 4;
	const char* argv[] = { "ssd.exe", WRITE_COMMAND, WRITE_ADDR, VALID_WRITE_VALUE };

	nandData = createMockNandData(0, NAND_DATA_EMPTY);
	EXPECT_CALL(mockedFileHandler, readFile(NAND_FILENAME))
		.Times(1)
		.WillOnce(Return(nandData));

	nandData = createMockNandData(std::stoi(WRITE_ADDR), VALID_WRITE_VALUE);
	EXPECT_CALL(mockedFileHandler, writeData(NAND_FILENAME, nandData))
		.Times(1);

	string expectedOutput = { WRITE_SUCCESS };
	EXPECT_CALL(mockedFileHandler, writeData(OUTPUT_FILENAME, expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}
#else
TEST_F(SSDFixture, run_with_w_1_0x00001111)
{
	int argc = 4;
	const char* argv[] = { "ssd.exe", WRITE_COMMAND, WRITE_ADDR, VALID_WRITE_VALUE };
	nandData = createMockNandData(std::stoi(WRITE_ADDR), VALID_WRITE_VALUE);

	EXPECT_CALL(mockedFileHandler, writeData(NAND_FILENAME, nandData))
		.Times(0);

	string expectedOutput = { WRITE_SUCCESS };
	EXPECT_CALL(mockedFileHandler, writeData(OUTPUT_FILENAME, expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}
#endif

TEST_F(SSDFixture, run_with_w_1_0xzzzzFFFF)
{
	int argc = 4;
	const char* argv[] = { "ssd.exe", WRITE_COMMAND, WRITE_ADDR, INVALID_WRITE_VALUE };

	string expectedOutput = { ERROR_MESSAGE };
	EXPECT_CALL(mockedFileHandler, writeData(OUTPUT_FILENAME, expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}