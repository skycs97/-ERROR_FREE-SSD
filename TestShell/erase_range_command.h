#pragma once
#include "command.h"
#include "command_factory.h"

class EraseRangeCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
	void printResult(const string& result, const string& lba) const;
private:
	EraseRangeCommand(const std::vector<std::string>& args);
	bool checkLbaRange(int startLBAIndex, int endLBAIndex) const;

	string startLBA;
	string endLBA;

	friend class EraseRangeCommandFactory;
};

class EraseRangeCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_ERASE_RANGE_HELP =
	" - Erases data from the specified StartLBA to EndLBA SSD.\n\n"
	"Usage\n"
	" erase_range [StartLBA] [endLBA]\n"
	"Example\n"
	" erase_range 0 9\n"
	" erase_range 85 99\n";
