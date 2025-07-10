#include "flush_command.h"
#include "logger.h"

namespace {
	const int numOfArgs = 0;
}

FlushCommand::FlushCommand(const std::vector<std::string>& args) : Command(CMD_FLUSH, ::numOfArgs)
{
}

void FlushCommand::run(const CommandRunner& cmdRunner) const
{
	string result = cmdRunner.flush();

	if (result == ERR) {
		throw std::runtime_error("flush error!");
	}

	std::cout << "flush success!\n";

	LOGGING_SHELL( result);
}

std::shared_ptr<Command> FlushCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_FLUSH) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::make_shared<FlushCommand>(args);
}
