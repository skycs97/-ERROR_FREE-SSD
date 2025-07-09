#include "flush_command.h"

namespace {
	const int numOfArgs = 0;
}

FlushCommand::FlushCommand(const std::vector<std::string>& args) : Command(CMD_FLUSH, ::numOfArgs)
{
}

void FlushCommand::run(const CommandRunner& cmdRunner) const
{
	string result = cmdRunner.flush();

	if (result == ERROR) {
		throw std::runtime_error("flush error!");
	}

	std::cout << "flush success!\n";
}

void FlushCommand::printHelp() const
{
}

std::shared_ptr<Command> FlushCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	return std::make_shared<FlushCommand>(args);
}
