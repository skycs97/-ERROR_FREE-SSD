#pragma once
#include <vector>
#include <string>
#include <map>

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
const std::string CMD_1_FULL_WRITE_AND_READ_COMPARE_SHORT = "1_";
const std::string CMD_1_FULL_WRITE_AND_READ_COMPARE = "1_FullWriteAndReadCompare";
const std::string CMD_2_PARTIAL_LBA_WRITE_SHORT = "2_";
const std::string CMD_2_PARTIAL_LBA_WRITE = "2_PartialLBAWrite";
const std::string CMD_3_WRITE_READ_AGING_SHORT = "3_";
const std::string CMD_3_WRITE_READ_AGING = "3_WriteReadAging";
const std::string CMD_ERASE = "erase";
const std::string CMD_ERASE_RANGE = "erase_range";

const vector<string> AVAILABLE_COMMAND_LIST = {
	CMD_HELP,
	CMD_READ,
	CMD_WRITE,
	CMD_EXIT,
	CMD_FULLWRITE,
	CMD_FULLREAD,
	CMD_1_FULL_WRITE_AND_READ_COMPARE,
	CMD_2_PARTIAL_LBA_WRITE,
	CMD_3_WRITE_READ_AGING,
	CMD_ERASE,
	CMD_ERASE_RANGE
};

const std::map<string, string> shortCommandToCommand = {
	{CMD_1_FULL_WRITE_AND_READ_COMPARE_SHORT, CMD_1_FULL_WRITE_AND_READ_COMPARE},
	{CMD_2_PARTIAL_LBA_WRITE_SHORT, CMD_2_PARTIAL_LBA_WRITE},
	{CMD_3_WRITE_READ_AGING_SHORT, CMD_3_WRITE_READ_AGING}
};

static const int MAX_LBA = 99;
static const int MIN_LBA = 0;

const std::string ERROR = "ERROR";
const std::string DONE = "DONE";
const std::string FAIL = "FAIL";
const std::string WRITESUCCESS = "";
const std::string ERASESUCCESS = "";