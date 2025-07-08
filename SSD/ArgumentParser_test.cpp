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

TEST(ArgumentParserTest, ReadCommandExceptionTest) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"R",
		"1000"
	};	

	EXPECT_THROW(parser.parse_args(3, argv), std::invalid_argument);
}

TEST(ArgumentParserTest, ReadCommandExceptionNotEnoughArgumentTest) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"R"		
	};

	EXPECT_THROW(parser.parse_args(2, argv), std::invalid_argument);
}

TEST(ArgumentParserTest, WriteCommandTest) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"W",
		"20",
		"0xAAAABBBB"
	};

	parser.parse_args(4, argv);

	EXPECT_EQ(ArgumentParser::WRITE_CMD, parser.getCmdType());
	EXPECT_EQ(20, parser.getAddr());
	EXPECT_EQ("0xAAAABBBB", parser.getData());
}

TEST(ArgumentParserTest, WriteCommandExceptionTest) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"W",
		"200",
		"0xAAAABBBB"
	};

	EXPECT_THROW(parser.parse_args(4, argv), std::invalid_argument);
}

TEST(ArgumentParserTest, WriteCommandDataExceptionTest) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"W",
		"20",
		"0xRRRRQQQQQ"
	};

	EXPECT_THROW(parser.parse_args(4, argv), std::invalid_argument);
}

TEST(ArgumentParserTest, WriteCommandExceptionNotEnoughArgumentTest1) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"W"
	};

	EXPECT_THROW(parser.parse_args(2, argv), std::invalid_argument);
}

TEST(ArgumentParserTest, WriteCommandExceptionNotEnoughArgumentTest2) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe",
		"W",
		"50"
	};

	EXPECT_THROW(parser.parse_args(3, argv), std::invalid_argument);
}

TEST(ArgumentParserTest, NoCommandExceptionTest) {
	ArgumentParser parser;
	const char* argv[] = {
		"ssd.exe"
	};

	EXPECT_THROW(parser.parse_args(1, argv), std::invalid_argument);
}