#pragma once
#include "command.h"
#include "command_factory.h"

class EraseRangeCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
	void printResult(const string& result, const string& lba) const;
private:
	EraseRangeCommand(const std::vector<std::string>& args);
	bool checkLBARange(int startLBAIndex, int endLBAIndex) const;

	string startLBA;
	string endLBA;

	friend class EraseRangeCommandFactory;
};

class EraseRangeCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};