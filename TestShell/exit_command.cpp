#include "exit_command.h"


void ExitCommand::run(const CommandRunner& cmdRunner) const
{
	exit(0);
}