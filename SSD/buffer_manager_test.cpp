#include "gmock/gmock.h"
#include "buffer_manager.h"
#include "file_handler_mock.h"
#include "nand_flash_memory_mock.h"
using namespace testing;

class BufferManagerFixture : public Test {
public:
	FileHandlerMock fileHandler;
	NandFlashMemoryMock nand;
	BufferManager manager{ &nand, &fileHandler };
};

TEST_F(BufferManagerFixture, WriteAndReadTest) {
	manager.addWriteCommand(10, "0x11112222");

	string output = "";
	EXPECT_TRUE(manager.read(10, output));
	EXPECT_EQ("0x11112222", output);
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
	manager.addWriteCommand(0,"0x12341234");

	EXPECT_EQ(1, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, SimpleTC3) {
	manager.addWriteCommand(0, "0x12341234");
	manager.addWriteCommand(1, "0x12341234");
	manager.addWriteCommand(2, "0x12341234");

	manager.flush();

	EXPECT_EQ(0, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, DISABLED_TC1) {
	manager.addEraseCommand(0, 5);
	manager.addEraseCommand(7, 5);
	manager.addEraseCommand(15, 5);

	// 최적화 할 수 없이 입력 하나하나가 버퍼에 기록됩니다.
	EXPECT_EQ(3, manager.getUsedBufferCount());
}

TEST_F(BufferManagerFixture, DISABLED_TC2) {
	manager.addWriteCommand(0, "0x11112222");
	manager.addWriteCommand(1, "0x22223333");
	manager.addWriteCommand(2, "0x33334444");

	// 최적화 할 수 없이 입력 하나하나가 버퍼에 기록됩니다.
	EXPECT_EQ(3, manager.getUsedBufferCount());
}