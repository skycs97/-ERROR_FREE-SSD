#pragma once
#include "command.h"

class WriteReadAging : public Command {
public:
	WriteReadAging(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
	};
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	string hexToString(unsigned int random_value) const;
};
