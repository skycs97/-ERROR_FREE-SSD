#include "helper.h"
#include "TEST_SHELL_CONFIG.h"
#include <iostream>

std::map<std::string, std::string> Helper::cmdHelpList{};

void Helper::printAllHelp() {
	for (auto cmdName : AVAILABLE_COMMAND_LIST) {
		printCmdHelp(cmdName);
	}
}

std::string Helper::getCmdHelp(const std::string& cmdName)
{
	if (Helper::cmdHelpList.find(cmdName) == Helper::cmdHelpList.end()) {
		return "";
	}

	return Helper::cmdHelpList[cmdName];
}

void Helper::printCmdHelp(const std::string& cmdName)
{
	std::cout << "** " << cmdName << " **\n";
	std::cout << getCmdHelp(cmdName) << "\n\n";
}

void Helper::registerCmd(const std::string& cmdName, const std::string& helpStr)
{
	Helper::cmdHelpList.insert({ cmdName, helpStr });
}

