#pragma once
#include "command.h"
#include "command_factory.h"

class PartialLBAWriteCommand : public Command {
public:
	PartialLBAWriteCommand(const std::vector<std::string>& cmd);
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	static const int REPEAT_COUNT = 30;
	const std::string WRITE_DATA{ "0x12341234" };
	std::vector<std::string> TestLbaList = { "4","0","3","1","2" };

	bool checkResult(const std::vector<std::string>& result) const;
	void printProcess() const;
};

class PartialLBAWriteCommandFactory : public CommandFactory {
public:
	std::shared_ptr<Command> makeCommand(const string& cmdName, const std::vector<string>& args) override;
};
