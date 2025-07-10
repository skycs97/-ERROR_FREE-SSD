#pragma once
#include "command.h"
#include "command_factory.h"

class HelpCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
private:
	HelpCommand(const std::vector<std::string>& args);

	friend class HelpCommandFactory;
};

class HelpCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_HELP_HELP = "";