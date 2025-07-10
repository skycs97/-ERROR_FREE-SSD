#pragma once
#include "command.h"
#include "command_factory.h"

class FullWriteCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result) const;
	void printHelp() const override;
private:
	FullWriteCommand(const std::vector<std::string>& args);
	string value;

	friend class FullWriteCommandFactory;
};

class FullWriteCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

