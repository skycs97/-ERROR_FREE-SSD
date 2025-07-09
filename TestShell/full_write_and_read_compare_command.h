#pragma once
#include "command.h"
#include "command_factory.h"

class FullWriteAndReadCompareCommand : public Command {
public:
	FullWriteAndReadCompareCommand(const std::vector<std::string>& args);
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	bool partialWrite(const CommandRunner& cmdRunner, int lba, int testSize, string data) const;
	bool partialRead(const CommandRunner& cmdRunner, int lba, int testSize) const;
};

class FullWriteAndReadCompareCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};


