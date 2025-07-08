#include "command_runner.h"

string CommandRunner::runCommand(vector<string> cmd) {
	string result = "";
	if (cmd[1] == "R") {
		result = ssdInterface->read(stoi(cmd[2]));
	}
	else if (cmd[1] == "W") {
		result = ssdInterface->write(stoi(cmd[2]), stoi(cmd[3]));
	}

	return result;
}

void CommandRunner::setStorage(SsdInterface* ssdInterface)
{
	this->ssdInterface = ssdInterface;
}

