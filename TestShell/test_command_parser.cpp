#include "gmock/gmock.h"
#include <string>
#include <vector>
#include "command_parser.h"

using namespace testing;
using std::string;
using std::vector;

TEST(CommandParserTest, Read) {
	CommandParser cmdParser;
	string inputCommand = "read 0";
	string expected = "read";
	auto cmd = cmdParser.parseAndMakeShellCommand(inputCommand);
	EXPECT_EQ(expected, cmd->getCmdName());
}

TEST(CommandParserTest, ReadWithWrongArgs) {
	CommandParser cmdParser;
	string inputCommand = "read 0 0";

	EXPECT_THROW(cmdParser.parseAndMakeShellCommand(inputCommand), TestScriptFailExcpetion);
}

TEST(CommandParserTest, Write) {
	CommandParser cmdParser;
	string inputCommand = "write 0 0x12341234";
	string expected = "write";
	auto cmd = cmdParser.parseAndMakeShellCommand(inputCommand);
	EXPECT_EQ(expected, cmd->getCmdName());
}

TEST(CommandParserTest, WriteWithWrongArgs) {
	CommandParser cmdParser;
	string inputCommand = "write 0 0 0";

	EXPECT_THROW(cmdParser.parseAndMakeShellCommand(inputCommand), TestScriptFailExcpetion);
}

TEST(CommandParserTest, Help) {
	CommandParser cmdParser;
	string inputCommand = "help";
	string expected = "help";
	auto cmd = cmdParser.parseAndMakeShellCommand(inputCommand);
	EXPECT_EQ(expected, cmd->getCmdName());

}

TEST(CommandParserTest, HelpWithWrongArgs) {
	CommandParser cmdParser;
	string inputCommand = "help 0";

	EXPECT_THROW(cmdParser.parseAndMakeShellCommand(inputCommand), TestScriptFailExcpetion);
}

TEST(CommandParserTest, Exit) {
	CommandParser cmdParser;
	string inputCommand = "exit";
	string expected = "exit";
	auto cmd = cmdParser.parseAndMakeShellCommand(inputCommand);
	EXPECT_EQ(expected, cmd->getCmdName());
}

TEST(CommandParserTest, ExitWithWrongArgs) {
	CommandParser cmdParser;
	string inputCommand = "exit 0";

	EXPECT_THROW(cmdParser.parseAndMakeShellCommand(inputCommand), TestScriptFailExcpetion);
}

TEST(CommandParserTest, InValidCommand) {
	CommandParser cmdParser;
	string inputCommand = "R 0";
	EXPECT_THROW(cmdParser.parseAndMakeShellCommand(inputCommand), TestScriptFailExcpetion);
}
