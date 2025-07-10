#include "gmock/gmock.h"
#include "ssd.h"
#include "file_handler_mock.h"
using namespace testing;

class SSDFixture : public Test {
protected:
	void SetUp() override {
		nandData = getNandDataForTesting();

		EXPECT_CALL(mockedFileHandler, isFileExistByMatchLength(_, _, _))
			.Times(1)
			.WillOnce(Return(true));

		EXPECT_CALL(mockedFileHandler, read(NAND_FILENAME))
			.WillRepeatedly(Return(nandData));

	}
public:
	NiceMock<FileHandlerMock> mockedFileHandler;
	SSD ssd{ &mockedFileHandler };
	vector<string> nandData;
	/*
	* 아래와 같은 값이 nand에 쓰여져 있다고 생각하고 값을 출력합니다.
	* 0	0x00000001
	* 1	0x00000002
	* ...
	* 99 0x0000063
	*/
	vector<string> getNandDataForTesting() {
		vector<string> ret;
		for (int i = 0; i < 100; i++) {
			std::ostringstream oss;
			// 10진수와 탭
			oss << i << '\t'
				// "0x" 접두사
				<< "0x"
				// 16진수, 소문자, 폭 8, '0' 채움
				<< std::hex << std::nouppercase << std::setw(8) << std::setfill('0')
				<< i;
			// 다시 10진수 모드로 복원(다음 루프에서 안전하게 사용하기 위해)
			oss << std::dec;

			ret.push_back(oss.str());
		}
		return ret;
	}
	string getNandDataOf(const char* addr) {
		int address = std::atoi(addr);
		string ret = nandData.at(address);
		int pos = ret.find("\t");
		return ret.substr(pos + 1);
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
};

TEST_F(SSDFixture, run_with_r_1)
{
	int argc = 3;
	const char* argv[] = { "ssd.exe", READ_COMMAND, READ_ADDR };
	vector<string> expectedOutput = { getNandDataOf(READ_ADDR) };
	EXPECT_CALL(mockedFileHandler, write(OUTPUT_FILENAME, expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}

TEST_F(SSDFixture, run_with_r_110)
{
	int argc = 3;
	const char* argv[] = { "ssd.exe", READ_COMMAND, INVALID_READ_ADDR };

	EXPECT_CALL(mockedFileHandler, write(OUTPUT_FILENAME, vector<string>{ERROR_MESSAGE}))
		.Times(1);

	ssd.run(argc, argv);
}

#if BUFFER_ENABLE == false
TEST_F(SSDFixture, run_with_w_1_0x00001111)
{
	int argc = 4;
	const char* argv[] = { "ssd.exe", WRITE_COMMAND, WRITE_ADDR, VALID_WRITE_VALUE };

	nandData[1] = VALID_NAND_DATA;
	EXPECT_CALL(mockedFileHandler, write(NAND_FILENAME, nandData))
		.Times(1);

	vector<string> expectedOutput = { WRITE_SUCCESS };
	EXPECT_CALL(mockedFileHandler, write(OUTPUT_FILENAME, expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}
#else
TEST_F(SSDFixture, run_with_w_1_0x00001111)
{
	int argc = 4;
	const char* argv[] = { "ssd.exe", WRITE_COMMAND, WRITE_ADDR, VALID_WRITE_VALUE };

	nandData[1] = VALID_NAND_DATA;
	EXPECT_CALL(mockedFileHandler, write(NAND_FILENAME, nandData))
		.Times(0);

	vector<string> expectedOutput = { WRITE_SUCCESS };
	EXPECT_CALL(mockedFileHandler, write(OUTPUT_FILENAME, expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}
#endif

TEST_F(SSDFixture, run_with_w_1_0xzzzzFFFF)
{
	int argc = 4;
	const char* argv[] = { "ssd.exe", WRITE_COMMAND, WRITE_ADDR, INVALID_WRITE_VALUE };

	vector<string> expectedOutput = { ERROR_MESSAGE };
	EXPECT_CALL(mockedFileHandler, write(OUTPUT_FILENAME, expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}