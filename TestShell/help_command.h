#pragma once
#include "command.h"

class HelpCommand : public Command {
public:

	HelpCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
	};

	void printHelp() const override;
	void run(const CommandRunner& cmdRunner) const override;
};
