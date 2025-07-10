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

void Command::printProcess(void) const
{
	std::cout << std::left << std::setw(25) << cmdName;
	std::cout << "  ___   " << "Run..";
}

bool Command::isValidLba(int lba) const
{
	if (lba<MIN_LBA || lba > MAX_LBA) return false;
	return true;
}
