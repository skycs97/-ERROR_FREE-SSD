#pragma once
#include "command.h"
#include "command_factory.h"

class ReadCommand : public Command {
public:
	ReadCommand(const std::vector<std::string>& args);

	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
	void printResult(const string& result, const string& lba) const;
	string LBA;
};

class ReadCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};