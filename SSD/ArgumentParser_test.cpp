#include "gmock/gmock.h"
#include "ArgumentParser.h"

using ::testing::Test;

class ArgumentParserFixture : public Test {
public:
	ArgumentParser parser;

};

TEST_F(ArgumentParserFixture, ReadCommandTest) {
	
	const char* argv[] = {
		"ssd.exe",
		"R",
		"10"
	};

	parser.parse_args(3, argv);

	EXPECT_EQ(ArgumentParser::READ_CMD, parser.getCmdType());
	EXPECT_EQ(10, parser.getAddr());
}

TEST_F(ArgumentParserFixture, ReadCommandExceptionTest) {
	const char* argv[] = {
		"ssd.exe",
		"R",
		"1000"
	};	

	EXPECT_THROW(parser.parse_args(3, argv), std::invalid_argument);
}

TEST_F(ArgumentParserFixture, ReadCommandExceptionNotEnoughArgumentTest) {
	const char* argv[] = {
		"ssd.exe",
		"R"		
	};

	EXPECT_THROW(parser.parse_args(2, argv), std::invalid_argument);
}

TEST_F(ArgumentParserFixture, WriteCommandTest) {
	const char* argv[] = {
		"ssd.exe",
		"W",
		"20",
		"0xAAAABBBB"
	};

	parser.parse_args(4, argv);

	EXPECT_EQ(ArgumentParser::WRITE_CMD, parser.getCmdType());
	EXPECT_EQ(20, parser.getAddr());
	EXPECT_EQ(0xAAAABBBB, parser.getData());
}

TEST_F(ArgumentParserFixture, WriteCommandExceptionTest) {
	const char* argv[] = {
		"ssd.exe",
		"W",
		"200",
		"0xAAAABBBB"
	};

	EXPECT_THROW(parser.parse_args(4, argv), std::invalid_argument);
}

TEST_F(ArgumentParserFixture, WriteCommandDataExceptionTest) {
	const char* argv[] = {
		"ssd.exe",
		"W",
		"20",
		"0xRRRRQQQQQ"
	};

	EXPECT_THROW(parser.parse_args(4, argv), std::invalid_argument);
}

TEST_F(ArgumentParserFixture, WriteCommandExceptionNotEnoughArgumentTest1) {
	const char* argv[] = {
		"ssd.exe",
		"W"
	};

	EXPECT_THROW(parser.parse_args(2, argv), std::invalid_argument);
}

TEST_F(ArgumentParserFixture, WriteCommandExceptionNotEnoughArgumentTest2) {
	const char* argv[] = {
		"ssd.exe",
		"W",
		"50"
	};

	EXPECT_THROW(parser.parse_args(3, argv), std::invalid_argument);
}

TEST_F(ArgumentParserFixture, NoCommandExceptionTest) {
	const char* argv[] = {
		"ssd.exe"
	};

	EXPECT_THROW(parser.parse_args(1, argv), std::invalid_argument);
}