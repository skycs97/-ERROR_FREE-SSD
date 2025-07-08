#pragma once
#include "command.h"

class FullWriteCommand : public Command {
public:

	FullWriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
		help = "fullwrite";
	};

	void run(const CommandRunner& cmdRunner) const override;
};

