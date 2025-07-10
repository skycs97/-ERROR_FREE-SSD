#pragma once
#include <map>
#include <string>

class Helper {
public:
	static void printAllHelp();
	static std::string getCmdHelp(const std::string& cmdName);
	static void printCmdHelp(const std::string& cmdName);
	static void registerCmd(const std::string& cmdName, const std::string& helpStr);
private:
	static std::map<std::string, std::string> cmdHelpList;
	Helper() = delete;
};
