#include "gmock/gmock.h"
#include "ssd.h"
#include "file_handler_mock.h"
using namespace testing;

class SSDFixture : public Test {
public:
	FileHandlerMock mockedFileHandler;
	SSD ssd{&mockedFileHandler};

	// mocking nand 데이터. 
	// n번째 addr의 값은 n의 16진수 표현. (ex  15\t0x0000000f )
	vector<string> getMockedData() {
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
};

TEST_F(SSDFixture, run_with_read_command)
{
	//1. ssd.exe r 0 호출시
	int argc = 3;
	const char* argv[] = {"ssd.exe", "r", "1" };

	//2. ssd_nand.txt에 아래와 같이 작성되어있다면
	vector<string> writtenData = getMockedData();
	EXPECT_CALL(mockedFileHandler, read("ssd_nand.txt"))
		.Times(1)
		.WillRepeatedly(Return(writtenData));

	//3. output에 0x00000001을 적길 기대합니다.
	vector<string> expectedOutput = { "0x00000001" };
	EXPECT_CALL(mockedFileHandler, write("ssd_output.txt", expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}

TEST_F(SSDFixture, run_with_read_command_but_invalid_addr)
{
	//1. ssd.exe r 110 호출시
	int argc = 3;
	const char* argv[] = { "ssd.exe", "r", "110" };

	//2. output에 ERROR를 적길 기대합니다.
	vector<string> expectedOutput = { "ERROR" };
	EXPECT_CALL(mockedFileHandler, write("ssd_output.txt", expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}