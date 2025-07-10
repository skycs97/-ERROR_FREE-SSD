#pragma once
#include "command.h"
#include "command_factory.h"

class EraseCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
	void printResult(const string& result, const string& lba) const;
private:
	EraseCommand(const std::vector<std::string>& args);

	string startLBA;
	string LBARange;

	friend class EraseCommandFactory;
};

class EraseCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};