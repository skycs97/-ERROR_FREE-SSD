#include <sstream>
#include "command_factory.h"

Command* FactoryCommand::makeCommand(const std::string& cmd)
{
	std::istringstream ss(cmd);
	std::string word;
	std::vector<std::string> commands;
	std::string shellCmd;

	while (ss >> word) {
		commands.push_back(word);
	}

	shellCmd = commands.front();

	if (shellCmd == CMD_READ) return new ReadCommand(commands);
	else if (shellCmd == CMD_WRITE) return new WriteCommand(commands);
	else if (shellCmd == CMD_EXIT) return new ExitCommand(commands);
	else if (shellCmd == CMD_HELP) return new HelpCommand(commands);
	else if (shellCmd == CMD_FULLWRITE) return new FullWriteCommand(commands);
	else if (shellCmd == CMD_FULLREAD) return new FullReadCommand(commands);
	else if ((CMD_1_FULLWRITEANDREADCOMPARE.find(shellCmd) != string::npos) || (shellCmd == CMD_1_FULLWRITEANDREADCOMPARE)) return new FullWriteAndReadCompare(commands);
	else if ((CMD_2_PartialLBAWrite.find(shellCmd) != string::npos) || (shellCmd == CMD_2_PartialLBAWrite)) return new PartialLBAWrite(commands);
	else if ((CMD_3_WRITEREADAGING.find(shellCmd) != string::npos) || (shellCmd == CMD_3_WRITEREADAGING)) return new WriteReadAging(commands);

	else return nullptr;
}