#include "gmock/gmock.h"
#include "ArgumentParser.h"


TEST(ArgumentParserTest, ReadCommandTest) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"R",
		"10"
	};

	parser.parse_args(3, argv);

	EXPECT_EQ(ArgumentParser::READ_CMD, parser.getCmdType());
	EXPECT_EQ(10, parser.getAddr());
}
