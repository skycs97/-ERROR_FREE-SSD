#pragma once
#include "command.h"

class FullWriteAndReadCompare : public Command {
public:
	FullWriteAndReadCompare(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
	};
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
};
