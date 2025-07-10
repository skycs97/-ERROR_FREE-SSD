#pragma once
#include "command.h"
#include "command_factory.h"

class EraseAndWriteAgingCommand : public Command {
public:
	EraseAndWriteAgingCommand(const std::vector<std::string>& args);
	void run(const CommandRunner& cmdRunner) const override;
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

const std::string CMD_4_ERASE_AND_WRITE_AGING_HELP =
	"** Erase Write Aging Command **\n"
	" - A test that erase & writes a random value to LBA 0 and 99, repeated 30 times..\n"
	"Usage\n"
	" 4_EraseAndWriteAging\n"
	" 4_\n";
