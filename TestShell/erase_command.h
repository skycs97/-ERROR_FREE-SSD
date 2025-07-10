#pragma once
#include "command.h"
#include "command_factory.h"

class EraseCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result, const string& lba) const;
private:
	EraseCommand(const std::vector<std::string>& args);
    bool checkLbaRange(int startLBAIndex, int range) const;

	string startLBA;
	string LBARange;

	friend class EraseCommandFactory;
};

class EraseCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_ERASE_HELP =
	" - Erases data from the specified StartLBA in range of LBARange SSD.\n\n"
	"Usage\n"
	" erase [StartLBA] [LBARange]\n"
	"Example\n"
	" erase 0 10\n"
	" erase 85 15\n";