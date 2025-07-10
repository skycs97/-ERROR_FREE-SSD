#include "gmock/gmock.h"
#include "read_command.h"
#include "output_handler.h"
#include "nand_flash_memory.h"
#include "nand_flash_memory_impl.h"
#include "buffer_manager.h"
#include "file_handler.h"

using ::testing::Test;

class SSDCommandTestFixture : public Test {
public:
	SSDCommandTestFixture() {
		// Create result IO instance
		FileHandler* fileHandler = new FileHandler();
		OutputHandler* outputHandler = new OutputHandler(fileHandler);

		// Create nand IO instance
		NandFlashMemoryImpl* nand = new NandFlashMemoryImpl(fileHandler);
		BufferManager* bufferManager = new BufferManager(nand, fileHandler);

		SSDCommandFactory* factory = new SSDCommandFactory();
	}

	// Create result IO instance
	FileHandler* fileHandler;
	OutputHandler* outputHandler;

	// Create nand IO instance
	NandFlashMemoryImpl* nand;
	BufferManager* bufferManager;

	SSDCommandFactory* factory;
};

TEST_F(SSDCommandTestFixture, ReadCommandOutOfRangeTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"R",
		"1000"
	};

	int argc = 3;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("Out of range", string(e.what()));
	}
}

TEST_F(SSDCommandTestFixture, ReadCommandInvalidAddrTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"R",
		"A"
	};

	int argc = 3;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("Not a number in address", string(e.what()));
	}
}

TEST_F(SSDCommandTestFixture, WriteCommandInvalidHexDataTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"W",
		"20",
		"0xQQQQZZZZ"
	};

	int argc = 4;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("Not a hex number in data", string(e.what()));
	}
}

TEST_F(SSDCommandTestFixture, WriteCommandShortHexDataTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"W",
		"20",
		"1000"
	};

	int argc = 4;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("Incorrect Hex number length in data", string(e.what()));
	}
}

TEST_F(SSDCommandTestFixture, WriteCommandIncorrectHexDataTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"W",
		"20",
		"0Z1000AAAA"
	};

	int argc = 4;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("Not a hexa digit format in data", string(e.what()));
	}
}

TEST_F(SSDCommandTestFixture, WriteCommandTooLongHexDataTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"W",
		"30",
		"0xAAAABBBBCCCC"
	};

	int argc = 4;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("Incorrect Hex number length in data", string(e.what()));
	}
}

TEST_F(SSDCommandTestFixture, EraseCommandInvalidCountTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"E",
		"91",
		"E"
	};

	int argc = 4;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("Not a number in count", string(e.what()));
	}
}

TEST_F(SSDCommandTestFixture, EraseCommandRangeOverTest) {
	// Arrange
	const char* argv[] = {
		"ssd.exe",
		"E",
		"91",
		"10"
	};

	int argc = 4;

	// Act
	SSDCommand* cmd = factory->createCommand(string(argv[ARG_IDX_CMD]), nand, bufferManager);

	// Assert
	try {
		cmd->parseArg(argc, argv);

	}
	catch (std::invalid_argument e)
	{
		EXPECT_EQ("The erase range exceeds the MAX_LBA", string(e.what()));
	}
}