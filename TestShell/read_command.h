#pragma once

#include "command.h"

class ReadCommand : public Command {
public:
	ReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 2;
		help = "read [LBA]";
	};

	void run(const CommandRunner& cmdRunner) const override;
};
