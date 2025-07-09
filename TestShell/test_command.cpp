#ifdef _DEBUG
#include "gmock/gmock.h"
#include <string>
#include <vector>
#include "command.h"
#include "command_factory_complex.h"
#include "command_parser.h"

class CommandFactoryTest : public testing::Test {
public:
	CommandParser parser;

	std::shared_ptr<Command> parseAndMakeShellCommand(const std::string& cmd) { 
		return parser.parseAndMakeShellCommand(cmd); 
	}
};
TEST_F(CommandFactoryTest, Read) {
	
	auto command = parseAndMakeShellCommand("read 0");

	EXPECT_TRUE(command->getNumOfArgs() == 1);
	EXPECT_EQ("read", command->getCmdName());
}

TEST_F(CommandFactoryTest, Write) {

	auto command = parseAndMakeShellCommand("write 0 1");

	EXPECT_TRUE(command->getNumOfArgs() == 2);
	EXPECT_EQ("write", command->getCmdName());
}

TEST_F(CommandFactoryTest, exit) {

	auto command = parseAndMakeShellCommand("exit");

	EXPECT_TRUE(command->getNumOfArgs() == 0);
	EXPECT_EQ("exit", command->getCmdName());
}

TEST_F(CommandFactoryTest, help) {
	auto command = parseAndMakeShellCommand("help");

	EXPECT_TRUE(command->getNumOfArgs() == 0);
	EXPECT_EQ("help", command->getCmdName());
}

TEST_F(CommandFactoryTest, fullwrite) {
	auto command = parseAndMakeShellCommand("fullwrite 0xAAAABBBB");

	EXPECT_TRUE(command->getNumOfArgs() == 1);
	EXPECT_EQ("fullwrite", command->getCmdName());
}

TEST_F(CommandFactoryTest, fullread) {

	auto command = parseAndMakeShellCommand("fullread");

	EXPECT_TRUE(command->getNumOfArgs() == 0);
	EXPECT_EQ("fullread", command->getCmdName());
}

TEST_F(CommandFactoryTest, Erase) {

	auto command = parseAndMakeShellCommand("erase 0 1");

	EXPECT_TRUE(command->getNumOfArgs() == 2);
	EXPECT_EQ("erase", command->getCmdName());
}

TEST_F(CommandFactoryTest, EraseInRage) {

	auto command = parseAndMakeShellCommand("erase_range 0 1");

	EXPECT_TRUE(command->getNumOfArgs() == 2);
	EXPECT_EQ("erase_range", command->getCmdName());
}
#endif
