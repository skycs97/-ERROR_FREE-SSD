#pragma once

#include "command.h"

class HelpCommand : public Command {
public:

	HelpCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "help";
	};

	void run(const CommandRunner& cmdRunner) const override;
};
