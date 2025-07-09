#pragma once
#include "command.h"
#include "command_factory.h"

class ExitCommand : public Command {
public:

	ExitCommand(const std::vector<std::string>& args);

	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
};

class ExitCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};