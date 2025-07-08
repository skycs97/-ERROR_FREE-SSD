#include "gmock/gmock.h"
#include "ssd.h"
#include "file_handler_mock.h"
using namespace testing;
TEST(SSD, run_with_read_command)
{
	// arrange
	FileHandlerMock mockedFileHandler;
	SSD ssd = SSD(&mockedFileHandler);

	//1. ssd.exe r 0 ȣ���
	int argc = 3;
	const char* argv[] = {"ssd.exe", "r", "0" };

	//2. ssd_nand.txt�� �Ʒ��� ���� �ۼ��Ǿ��ִٸ�
	vector<string> writtenData = { "0\t0x11111111","1\t0x22222222" };
	EXPECT_CALL(mockedFileHandler, read("ssd_nand.txt"))
		.Times(1)
		.WillRepeatedly(Return(writtenData));

	//3. output�� 0x11111111�� ���� ����մϴ�.
	vector<string> expectedOutput = { "0x11111111" };
	EXPECT_CALL(mockedFileHandler, write("ssd_output.txt", expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}