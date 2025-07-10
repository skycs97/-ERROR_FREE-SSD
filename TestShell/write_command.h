#pragma once
#include "command.h"
#include "command_factory.h"

class WriteCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result) const;
	void printHelp() const override;
private:
	string LBA;
	string value;

	WriteCommand(const std::vector<std::string>& args);

	friend class WriteCommandFactory;
};

class WriteCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};
