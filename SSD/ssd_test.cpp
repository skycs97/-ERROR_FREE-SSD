#include "gmock/gmock.h"
#include "ssd.h"
#include "file_handler_mock.h"
using namespace testing;

class SSDFixture : public Test {
public:
	FileHandlerMock mockedFileHandler;
	SSD ssd{&mockedFileHandler};

	// mocking nand ������. 
	// n��° addr�� ���� n�� 16���� ǥ��. (ex  15\t0x0000000f )
	vector<string> getMockedData() {
		vector<string> ret;
		for (int i = 0; i < 100; i++) {
			std::ostringstream oss;
			// 10������ ��
			oss << i << '\t'
				// "0x" ���λ�
				<< "0x"
				// 16����, �ҹ���, �� 8, '0' ä��
				<< std::hex << std::nouppercase << std::setw(8) << std::setfill('0')
				<< i;
			// �ٽ� 10���� ���� ����(���� �������� �����ϰ� ����ϱ� ����)
			oss << std::dec;

			ret.push_back(oss.str());
		}
		return ret;
	}
};

TEST_F(SSDFixture, run_with_read_command)
{
	//1. ssd.exe r 0 ȣ���
	int argc = 3;
	const char* argv[] = {"ssd.exe", "r", "1" };

	//2. ssd_nand.txt�� �Ʒ��� ���� �ۼ��Ǿ��ִٸ�
	vector<string> writtenData = getMockedData();
	EXPECT_CALL(mockedFileHandler, read("ssd_nand.txt"))
		.Times(1)
		.WillRepeatedly(Return(writtenData));

	//3. output�� 0x00000001�� ���� ����մϴ�.
	vector<string> expectedOutput = { "0x00000001" };
	EXPECT_CALL(mockedFileHandler, write("ssd_output.txt", expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}

TEST_F(SSDFixture, run_with_read_command_but_invalid_addr)
{
	//1. ssd.exe r 110 ȣ���
	int argc = 3;
	const char* argv[] = { "ssd.exe", "r", "110" };

	//2. output�� ERROR�� ���� ����մϴ�.
	vector<string> expectedOutput = { "ERROR" };
	EXPECT_CALL(mockedFileHandler, write("ssd_output.txt", expectedOutput))
		.Times(1);

	ssd.run(argc, argv);
}