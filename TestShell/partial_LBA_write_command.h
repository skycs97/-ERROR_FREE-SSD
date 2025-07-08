#pragma once
#include "command.h"

class PartialLBAWrite : public Command {
public:
	PartialLBAWrite(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 1;
	};
	void run(const CommandRunner& cmdRunner) const override;
	void printHelp() const override;
private:
	static const int REPEAT_COUNT = 30;
	const std::string WRITE_DATA{ "0x12341234" };
	std::vector<std::string> TestLbaList = { "4","0","3","1","2" };

	bool checkResult(const std::vector<std::string>& result) const;
};
