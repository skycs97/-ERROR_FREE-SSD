#pragma once
#include "command.h"

class FullWriteAndReadCompare : public Command {
public:
	FullWriteAndReadCompare(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
	};
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	bool partialWrite(const CommandRunner& cmdRunner, int lba, int testSize, string data) const;
	bool partialRead(const CommandRunner& cmdRunner, int lba, int testSize) const;
};
