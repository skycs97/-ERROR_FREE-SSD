#include "gmock/gmock.h"
#include <string>
#include <vector>
#include "command.h"
#include "command_factory.h"

class CommandFactoryTest : public testing::Test {
public:
	FactoryCommand fc;

	Command* getCommand(const std::string& cmd) { return fc.makeCommand(cmd); }
};
TEST_F(CommandFactoryTest, Read) {
	
	Command* command = getCommand("read 0");

	EXPECT_TRUE(command->getNumOfArgs() == 2);
	EXPECT_EQ("read", command->getShellCommands().front());
}

TEST_F(CommandFactoryTest, Write) {

	Command* command = getCommand("write 0 1");

	EXPECT_TRUE(command->getNumOfArgs() == 3);
	EXPECT_EQ("write", command->getShellCommands().front());
}

TEST_F(CommandFactoryTest, exit) {

	Command* command = getCommand("exit");

	EXPECT_TRUE(command->getNumOfArgs() == 1);
	EXPECT_EQ("exit", command->getShellCommands().front());
}

TEST_F(CommandFactoryTest, help) {

	Command* command = getCommand("help");

	EXPECT_TRUE(command->getNumOfArgs() == 1);
	EXPECT_EQ("help", command->getShellCommands().front());
}

TEST_F(CommandFactoryTest, fullwrite) {

	Command* command = getCommand("fullwrite");

	EXPECT_TRUE(command->getNumOfArgs() == 1);
	EXPECT_EQ("fullwrite", command->getShellCommands().front());
}

TEST_F(CommandFactoryTest, fullread) {

	Command* command = getCommand("fullread");

	EXPECT_TRUE(command->getNumOfArgs() == 1);
	EXPECT_EQ("fullread", command->getShellCommands().front());
}