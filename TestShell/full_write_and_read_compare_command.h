#pragma once
#include "command.h"
#include "command_factory.h"

class FullWriteAndReadCompareCommand : public Command {
public:
	FullWriteAndReadCompareCommand(const std::vector<std::string>& args);
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	bool partialWrite(const CommandRunner& cmdRunner, int lba, int testSize, const vector<string>& data) const;
	bool partialReadAndCompare(const CommandRunner& cmdRunner, int lba, int testSize, const vector<string>& data) const;
	vector<string> getTestData(int testsize, int random) const;
};

class FullWriteAndReadCompareCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};


