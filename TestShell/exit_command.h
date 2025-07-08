#pragma once

#include "command.h"

class ExitCommand : public Command {
public:

	ExitCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "exit";
	};

	void run(const CommandRunner& cmdRunner) const override;
};
