#pragma once
#include "command.h"
#include "command_factory.h"

class ReadCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result, const string& lba) const;
	string LBA;
private:
	ReadCommand(const std::vector<std::string>& args);

	friend class ReadCommandFactory;
};

class ReadCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_READ_HELP =
	" - Reads data from the specified LBA from SSD.\n\n"
	"Usage\n"
	" read [LBA]\n"
	"Example\n"
	" read 0\n"
	" read 10\n";
