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
	vector<string> exepct = { "./ssd.exe", "R", "0" };
	EXPECT_EQ(exepct, cmdParser.getCommand(inputCommand));
}

TEST(CommandParserTest, Write) {
	CommandParser cmdParser;
	string inputCommand = "write 0 0x12341234";
	vector<string> exepct = { "./ssd.exe", "W", "0", "0x12341234" };
	EXPECT_EQ(exepct, cmdParser.getCommand(inputCommand));
}

TEST(CommandParserTest, Help) {
	CommandParser cmdParser;
	string inputCommand = "help";
	string exepct = "help";
	EXPECT_EQ(exepct, cmdParser.getCommand(inputCommand)[0]);
}

TEST(CommandParserTest, Exit) {
	CommandParser cmdParser;
	string inputCommand = "exit";
	string exepct = "exit";
	EXPECT_EQ(exepct, cmdParser.getCommand(inputCommand)[0]);
}

TEST(CommandParserTest, InValidCommand) {
	CommandParser cmdParser;
	string inputCommand = "R 0";
	EXPECT_THROW(cmdParser.getCommand(inputCommand), std::invalid_argument);
}
