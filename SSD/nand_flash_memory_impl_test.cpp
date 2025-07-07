#include "gmock/gmock.h"
#include "nand_flash_memory_impl.h"
#include "FileHandler.h"
#include <vector>
#include <string>

using namespace testing;
using std::vector;

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(void, write, (const std::string&), (override));
	MOCK_METHOD(std::string, read, (), (override));
};

TEST(NandFlashMemoryImpl, readTest) {
	FileHandlerMock mockedFileHandler;
	NandFlashMemoryImpl memory{ &mockedFileHandler };

	string writtenDatas= "0   0x00000000\n1   0x00000001\n";
	EXPECT_CALL(mockedFileHandler, read()).WillRepeatedly(Return(writtenDatas));
	vector<string> expected = { "0x00000000", "0x00000001" };
	vector<string> actual = memory.read();

	EXPECT_EQ(expected, actual);
}

