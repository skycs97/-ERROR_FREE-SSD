#include "full_read_command.h"

void FullReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_ADDR; lba <= MAX_ADDR; lba++) {
		result.push_back(cmdRunner.read(ShellCommands[1]));
	}
}