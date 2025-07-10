#pragma once
#include "command.h"
#include "command_factory.h"

class WriteCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result) const;
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

const std::string CMD_WRITE_HELP =
	" - Writes value to the specified LBA of SSD.\n"
	"Usage\n"
	" write [LBA] [value]\n"
	"Example\n"
	" write 0 0xAAAABBBB\n"
	" write 10 0x10002000\n";
