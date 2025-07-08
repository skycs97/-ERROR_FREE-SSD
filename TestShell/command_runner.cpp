#include "command_runner.h"
#include <stdexcept>
string CommandRunner::runCommand(vector<string> cmd) {
	if (ssdInterface == nullptr) {
		throw std::runtime_error("ssd Interface hasn't set");
	}

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

