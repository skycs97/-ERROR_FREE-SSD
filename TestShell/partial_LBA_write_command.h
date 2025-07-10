#pragma once
#include "command.h"
#include "command_factory.h"

class PartialLBAWriteCommand : public Command {
public:
	void run(const CommandRunner& cmdRunner) const override;
private:
	static const int REPEAT_COUNT = 30;
	const std::string WRITE_DATA{ "0x12341234" };
	std::vector<std::string> TestLbaList = { "4","0","3","1","2" };

	bool checkResult(const std::vector<std::string>& result) const;
	PartialLBAWriteCommand(const std::vector<std::string>& cmd);

	friend class PartialLBAWriteCommandFactory;
};

class PartialLBAWriteCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};

const std::string CMD_2_PARTIAL_LBA_WRITE_HELP =
	" - Write a specific value to several LBAs and then read it to check the value.\n"
	"Usage\n"
	" 2_PartialLBAWrite\n"
	" 2_\n";
