#pragma once
#include "command.h"
#include "command_factory.h"

class FullReadCommand : public Command {
public:

	FullReadCommand(const std::vector<std::string>& args);

	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result, const string& lba) const;
	void printHelp() const override;
};

class FullReadCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};