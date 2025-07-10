#pragma once
#include "command.h"
#include "command_factory.h"

class ExitCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
private:
	ExitCommand(const std::vector<std::string>& args);

	friend class ExitCommandFactory;
};

class ExitCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_EXIT_HELP =
	" - Exit Test Shell .\n"
	"Usage\n"
	" exit\n";
