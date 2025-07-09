#pragma once
#include "command.h"

class FullReadCommand : public Command {
public:

	FullReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
	};

	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result, const string& lba) const;
	void printHelp() const override;
};
