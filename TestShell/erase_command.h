#pragma once
#include "command.h"
#include "command_factory.h"

class EraseCommand : public Command {
public:
	EraseCommand(const std::vector<std::string>& args);

	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
	void printResult(const string& result, const string& lba) const;
private:
	string startLBA;
	string LBARange;
};

class EraseCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};