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

const vector<string> AVAILABLE_COMMAND_LIST = {
	CMD_READ,
	CMD_WRITE,
	CMD_EXIT,
	CMD_HELP,
	CMD_FULLWRITE,
	CMD_FULLREAD
};