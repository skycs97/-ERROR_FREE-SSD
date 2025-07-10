#pragma once
#include "command.h"
#include "command_factory.h"

class WriteReadAgingCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
private:
	WriteReadAgingCommand(const std::vector<std::string>& args);
	static const int REPEAT_COUNT = 200;
	friend class WriteReadAgingCommandFactory;
};

class WriteReadAgingCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_3_WRITE_READ_AGING_HELP =
	" - A test that writes a random value to LBA 0 and 99 and then reads it to confirm, repeated 200 times..\n"
	"Usage\n"
	" 3_WriteReadAging\n"
	" 3_\n";
