#pragma once
#include "command.h"

class WriteCommand : public Command {
public:

	WriteCommand(std::vector<std::string> cmd) : Command(cmd) {
		numOfArgs = 3;
		help = "write [LBA] [data]";
	};

	void run(const CommandRunner& cmdRunner) const override;
};
