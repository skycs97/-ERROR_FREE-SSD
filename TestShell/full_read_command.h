#pragma once
#include "command.h"

class FullReadCommand : public Command {
public:

	FullReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "fullread";
	};

	void run(const CommandRunner& cmdRunner) const override;
};
