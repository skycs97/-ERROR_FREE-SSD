#pragma once
#include "command.h"
#include "command_factory.h"

class EraseRangeCommand : public Command {
public:
	EraseRangeCommand(const std::vector<std::string>& args);

	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
	void printResult(const string& result, const string& lba) const;
private:
	string startLBA;
	string endLBA;
};

class EraseRangeCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};