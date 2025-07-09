#pragma once
#include "command.h"
#include "command_factory.h"

class WriteReadAgingCommand : public Command {
public:
	WriteReadAgingCommand(const std::vector<std::string>& args);
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	string hexToString(unsigned int random_value) const;
	void printProcess() const;
};

class WriteReadAgingCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};
