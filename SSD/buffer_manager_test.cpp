#include "gmock/gmock.h"
#include "buffer_manager.h"
#include "file_handler_mock.h"
#include "nand_flash_memory_impl.h"
using namespace testing;

class BufferManagerFixture : public Test {
protected:
	void SetUp() override {
		nandData = getNandDataForTesting();

		EXPECT_CALL(fileHandler, read(NAND_FILENAME))
			.WillRepeatedly(Return(nandData));
	}
public:
	FileHandlerMock fileHandler;
	NandFlashMemoryImpl nand{ &fileHandler };
	BufferManager manager{ &nand, &fileHandler };
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
};

TEST_F(BufferManagerFixture, WriteAndReadTest) {
	manager.addWriteCommand(10, "0x11112222");

	string output = "";
	EXPECT_TRUE(manager.read(10, output));
	EXPECT_EQ("0x11112222", output);
}

TEST_F(BufferManagerFixture, EraseAndReadTest) {
	manager.addEraseCommand(7, 5);

	string output = "";
	EXPECT_TRUE(manager.read(10, output));
	EXPECT_EQ("0x00000000", output);
}

TEST_F(BufferManagerFixture, ReadFailTest) {
	string output = "";
	EXPECT_FALSE(manager.read(10, output));
}

TEST_F(BufferManagerFixture, SimpleTC1) {
	manager.addEraseCommand(0, 5);

	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, SimpleTC2) {
	manager.addWriteCommand(0, "0x12341234");

	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, SimpleTC3) {
	manager.addWriteCommand(0, "0x12341234");
	manager.addWriteCommand(1, "0x12341234");
	manager.addWriteCommand(2, "0x12341234");

	manager.flush();

	EXPECT_EQ(0, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, TC1) {
	manager.addEraseCommand(0, 5);
	manager.addEraseCommand(7, 5);
	manager.addEraseCommand(15, 5);

	// 최적화 할 수 없이 입력 하나하나가 버퍼에 기록됩니다.
	EXPECT_EQ(3, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, TC2) {
	manager.addWriteCommand(0, "0x11112222");
	manager.addWriteCommand(1, "0x22223333");
	manager.addWriteCommand(2, "0x33334444");

	// 최적화 할 수 없이 입력 하나하나가 버퍼에 기록됩니다.
	EXPECT_EQ(3, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, TC3) {
	manager.addWriteCommand(0, "0x11112222");
	manager.addWriteCommand(1, "0x22223333");
	manager.addWriteCommand(2, "0x33334444");
	manager.addWriteCommand(3, "0x44445555");
	manager.addWriteCommand(4, "0x55556666");
	manager.addWriteCommand(5, "0x66667777");

	// 마지막 명령어 수행시 flush 가 발생해 used 버퍼에는 마지막 명령어만 남아있습니다.
	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, DISABLED_TC4) {
	manager.addEraseCommand(0, 3);
	manager.addEraseCommand(3, 3);

	// E 0 6 으로 최적화 가능합니다.
	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, DISABLED_TC5) {
	manager.addEraseCommand(0, 3);
	manager.addWriteCommand(3, "0x00000000");

	//W 3 0x00000000 은 E 3 1 과 동일합니다. 따라서 E 0 4 로 최적화됩니다.
	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, DISABLED_TC6) {
	manager.addWriteCommand(1, "0x11112222");
	manager.addWriteCommand(10, "0xFAFAFAFA");
	manager.addWriteCommand(1, "0x0000DDDD");

	// 마지막에 들어온 W 1 에 의해 앞선 W 1 0x11112222는 지워집니다
	EXPECT_EQ(2, manager.getUsedBufferCount());
	string output = "";
	manager.read(1, output);
	EXPECT_EQ("0x0000DDDD", output);
}


TEST_F(BufferManagerFixture, DISABLED_TC7) {
	manager.addWriteCommand(3, "0x11112222");
	manager.addEraseCommand(0, 5);
	manager.addWriteCommand(4, "0x22224444");

	// E 0 5 에 의해 W 3 0x11112222 가 지워집니다.
	EXPECT_EQ(2, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, DISABLED_TC8) {
	manager.addEraseCommand(0, 2);
	manager.addWriteCommand(2, "0x11112222");
	manager.addEraseCommand(3, 2);

	// E 0 5 
	// W 2 0x11112222 로 최적화가 됩니다.
	EXPECT_EQ(2, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, TC9) {
	manager.addEraseCommand(0, 2);
	manager.addWriteCommand(2, "0x11112222");
	manager.addEraseCommand(3, 9);

	// TC8과 달리 최적화가 되지 않아 그대로 버퍼에 담깁니다.
	EXPECT_EQ(3, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, DISABLED_TC10) {
	manager.addEraseCommand(0, 3);
	manager.addWriteCommand(1, "0x11111111");
	manager.addWriteCommand(2, "0x22222222");
	manager.addWriteCommand(3, "0ㅌ3333333");

	// E 0 3 이 이후에 들어온 W 명령어들에 의해 지워집니다.
	EXPECT_EQ(3, manager.getUsedBufferCount());
}