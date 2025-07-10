#define _CRT_SECURE_NO_WARNINGS
#include "gmock/gmock.h"
#include "buffer_manager.h"
#include "file_handler_mock.h"
#include "nand_flash_memory_impl.h"
using namespace testing;

class BufferManagerFixture : public Test {
protected:
	void SetUp() override {
		nandData = createMockNandData();

		EXPECT_CALL(fileHandler, readFile(NAND_FILENAME))
			.WillRepeatedly(Return(nandData));
	}

public:
	char* createMockNandData() {
		std::ostringstream oss;
		for (int i = MIN_LBA; i <= MAX_LBA; i++) {
			oss << std::setw(2) << std::setfill('0') << std::dec << i << '\t'
				<< "0x" << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << 0
				<< '\n';
		}

		std::string str = oss.str();

		// 동적 메모리 할당 (null-terminated)
		char* nandData = new char[str.size() + 1];
		std::strcpy(nandData, str.c_str());

		return nandData;
	}

	NiceMock<FileHandlerMock> fileHandler;
	NandFlashMemoryImpl nand{ &fileHandler };
	BufferManager manager{ &nand, &fileHandler };
	char* nandData;
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

TEST_F(BufferManagerFixture, TC4) {
	manager.addEraseCommand(0, 3);
	manager.addEraseCommand(3, 3);

	// E 0 6 으로 최적화 가능합니다.
	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, TC5) {
	manager.addEraseCommand(0, 3);
	manager.addWriteCommand(3, "0x00000000");

	//W 3 0x00000000 은 E 3 1 과 동일합니다. 따라서 E 0 4 로 최적화됩니다.
	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, TC6) {
	manager.addWriteCommand(1, "0x11112222");
	manager.addWriteCommand(10, "0xFAFAFAFA");
	manager.addWriteCommand(1, "0x0000DDDD");

	// 마지막에 들어온 W 1 에 의해 앞선 W 1 0x11112222는 지워집니다
	EXPECT_EQ(2, manager.getUsedBufferCount());
	string output = "";
	manager.read(1, output);
	EXPECT_EQ("0x0000DDDD", output);
}


TEST_F(BufferManagerFixture, TC7) {
	manager.addWriteCommand(3, "0x11112222");
	manager.addEraseCommand(0, 5);
	manager.addWriteCommand(4, "0x22224444");

	// E 0 5 에 의해 W 3 0x11112222 가 지워집니다.
	EXPECT_EQ(2, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, TC8) {
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

TEST_F(BufferManagerFixture, TC10) {
	manager.addEraseCommand(0, 3);
	manager.addWriteCommand(1, "0x11111111");
	manager.addWriteCommand(2, "0x22222222");
	manager.addWriteCommand(0, "0x33333333");

	// E 0 3 이 이후에 들어온 W 명령어들에 의해 지워집니다.
	EXPECT_EQ(3, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, FileNameTest1) {
	manager.init();
	EXPECT_CALL(fileHandler, rename(_, "buffer\\1_E_0_3"))
		.Times(1);
	manager.addEraseCommand(0, 3);
}

TEST_F(BufferManagerFixture, FileNameTest2) {
	manager.init();
	EXPECT_CALL(fileHandler, rename(_, "buffer\\1_W_10_0x11111111"))
		.Times(1);
	manager.addWriteCommand(10, "0x11111111");
}

TEST_F(BufferManagerFixture, InitEraseAndEraseTest) {
	EXPECT_CALL(fileHandler, isFileExistByMatchLength(_, _, _))
		.WillOnce(Return(false))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));
	EXPECT_CALL(fileHandler, getFileUsingPrefix)
		.WillOnce(Return(vector<string>{"1_E_0_3"}));
	EXPECT_CALL(fileHandler, rename("buffer\\1_E_0_3", "buffer\\1_E_0_5"))
		.Times(1);
	manager.init();
	
	manager.addEraseCommand(0, 5);
}

TEST_F(BufferManagerFixture, InitWriteAndEraseTest) {
	EXPECT_CALL(fileHandler, isFileExistByMatchLength(_, _, _))
		.WillOnce(Return(false))
		.WillOnce(Return(true))
		.WillRepeatedly(Return(false));
	EXPECT_CALL(fileHandler, getFileUsingPrefix)
		.WillOnce(Return(vector<string>{"1_W_0_0x11112222"}));
	EXPECT_CALL(fileHandler, rename("buffer\\1_W_0_0x11112222", "buffer\\1_E_0_5"))
		.Times(1);
	manager.init();

	manager.addEraseCommand(0, 5);
}

TEST_F(BufferManagerFixture, MAXLBA_TEST) {
	manager.addEraseCommand(97, 3);
	manager.addWriteCommand(99, "0x11111111");

	EXPECT_EQ(2, manager.getUsedBufferCount());
}