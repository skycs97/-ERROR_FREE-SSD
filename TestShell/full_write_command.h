#pragma once
#include "command.h"

class FullWriteCommand : public Command {
public:

	FullWriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
	};

	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result) const;
	void printHelp() const override;

};

