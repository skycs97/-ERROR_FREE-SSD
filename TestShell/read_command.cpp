#include "read_command.h"

void ReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.read(ShellCommands[1]));
}
