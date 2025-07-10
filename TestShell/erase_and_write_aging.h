#pragma once
#include "command.h"
#include "command_factory.h"

class EraseAndWriteAgingCommand : public Command {
public:
	EraseAndWriteAgingCommand(const std::vector<std::string>& args);
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	static const int REPEAT_COUNT = 30;
	int getLbaRange(int startLBA) const;
	void runEraseAndWrite(const CommandRunner& cmdRunner) const;
	string writeTwiceRandomData(const CommandRunner& cmdRunner, int startLBA) const;
};

class EraseAndWriteAgingCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};