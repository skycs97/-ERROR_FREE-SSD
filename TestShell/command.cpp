#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "command.h"
#include "command_runner.h"
#include "TEST_SHELL_CONFIG.h"

Command::Command(std::vector<std::string> commands) : ShellCommands(commands)
{
}

std::vector<std::string> Command::getShellCommands(void) {
	return ShellCommands;
}

int Command::getNumOfArgs(void) {
	return numOfArgs;
}