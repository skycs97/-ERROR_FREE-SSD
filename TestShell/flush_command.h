#pragma once
#include "command.h"
#include "command_factory.h"

class FlushCommand : public Command {
public:
	FlushCommand(const std::vector<std::string>& args);

	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
};

class FlushCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};
