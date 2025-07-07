#include "command_runner.h"

CommandRunner::CommandRunner(Storage* storage)
	: storage(storage)
{
}

string CommandRunner::runCommand(vector<string> cmd) {
	string result = "";
	if (cmd[1] == "R") {
		result = storage->read(stoi(cmd[2]));
	}
	else if (cmd[1] == "W") {
		result = storage->write(stoi(cmd[2]), stoi(cmd[3]));
	}

	return result;
}

