#pragma once
#include "command.h"
#include "command_factory.h"

class FullWriteCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result) const;
private:
	FullWriteCommand(const std::vector<std::string>& args);
	string value;

	friend class FullWriteCommandFactory;
};

class FullWriteCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_FULLWRITE_HELP =
	" - Writes value to the all LBAs in SSD.\n"
	"Usage\n"
	" fullwrite [value]\n"
	"Example\n"
	" fullwrite 0xAAAABBBBB\n"
	" fullwrite 0x10002000\n";
