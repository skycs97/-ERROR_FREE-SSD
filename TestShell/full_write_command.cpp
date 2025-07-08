#include "full_write_command.h"

void FullWriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_ADDR; lba <= MAX_ADDR; lba++) {
		result.push_back(cmdRunner.write(ShellCommands[1], ShellCommands[2]));
	}
}