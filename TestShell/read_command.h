#pragma once
#include "command.h"

class ReadCommand : public Command {
public:
	ReadCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 2;
	};

	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
	void printResult(const string& result, const string& lba) const;
};
