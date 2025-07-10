#include <iostream>
#include <sstream>
#include "command_factory.h"
#include "help_command.h"
#include "helper.h"

namespace {
	const int numOfArgs = 0;
}
std::string join(std::vector<std::string> const& strings, std::string delim)
{
	std::stringstream ss;
	std::copy(strings.begin(), strings.end(),
		std::ostream_iterator<std::string>(ss, delim.c_str()));
	return ss.str();
}

HelpCommand::HelpCommand(const std::vector<std::string>& args) : Command(CMD_HELP, ::numOfArgs)
{
}

void HelpCommand::run(const CommandRunner& cmdRunner) const
{
	std::cout << "------------------- Command Helper ------------------\n";
	Helper::printAllHelp();
	std::cout << std::endl;
	std::cout << "-------------------Thanks For Developers-------------------------\n";
	std::cout << join(DEVELOPERS, ", ") << "\n\n";
}

std::shared_ptr<Command> HelpCommandFactory::makeCommand(const string& cmdName, const std::vector<string>& args)
{
	if (cmdName != CMD_HELP) return nullptr;
	if (args.size() != numOfArgs) return nullptr;

	return std::shared_ptr<HelpCommand>(new HelpCommand(args));
}
