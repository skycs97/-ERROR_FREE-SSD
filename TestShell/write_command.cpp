#include "write_command.h"

void WriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.write(ShellCommands[1], ShellCommands[2]));
}
