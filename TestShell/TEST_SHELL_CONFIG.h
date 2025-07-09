#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

const vector<string> DEVELOPERS = {
	"skycs97",
	"choo4r",
	"dongs83",
	"iamsoonwonchoi",
	"JIeunAmy",
	"julysky123",
	"zeroexit-ryu"
};

//Commands
const std::string CMD_READ = "read";
const std::string CMD_WRITE = "write";
const std::string CMD_EXIT = "exit";
const std::string CMD_HELP = "help";
const std::string CMD_FULLWRITE = "fullwrite";
const std::string CMD_FULLREAD = "fullread";
const std::string CMD_1_FULLWRITEANDREADCOMPARE = "1_FullWriteAndReadCompare";
const std::string CMD_2_PartialLBAWrite = "2_PartialLBAWrite";
const std::string CMD_3_WRITEREADAGING = "3_WriteReadAging";

const vector<string> AVAILABLE_COMMAND_LIST = {
	CMD_HELP,
	CMD_READ,
	CMD_WRITE,
	CMD_EXIT,
	CMD_FULLWRITE,
	CMD_FULLREAD,
	CMD_1_FULLWRITEANDREADCOMPARE,
	CMD_2_PartialLBAWrite,
	CMD_3_WRITEREADAGING
};

static const int MAX_LBA = 99;
static const int MIN_LBA = 0;

const std::string ERROR = "ERROR";
const std::string DONE = "DONE";