#pragma once
#include "command.h"

class WriteCommand : public Command {
public:

	WriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 3;
	};

	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
};
