#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "command.h"
#include "command_runner.h"
#include "TEST_SHELL_CONFIG.h"


Command::Command(const string& cmdName, const int numOfArgs) : cmdName(cmdName), numOfArgs(numOfArgs)
{
}

int Command::getNumOfArgs(void) {
	return numOfArgs;
}

string Command::getCmdName(void)
{
	return cmdName;
}
