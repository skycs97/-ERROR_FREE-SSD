#include "help_command.h"
#include <iostream>
#include <sstream>
#include "command_factory.h"

std::string join(std::vector<std::string> const& strings, std::string delim)
{
	std::stringstream ss;
	std::copy(strings.begin(), strings.end(),
		std::ostream_iterator<std::string>(ss, delim.c_str()));
	return ss.str();
}

void HelpCommand::printHelp() const
{
	std::cout << "------------------- Command Helper ------------------\n";
}

void HelpCommand::run(const CommandRunner& cmdRunner) const
{
	FactoryCommand factory;
	for (const string& cmd : AVAILABLE_COMMAND_LIST) {
		factory.makeCommand(cmd)->printHelp();
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "-------------------Thanks For Developers-------------------------\n";
	std::cout << join(DEVELOPERS, ", ") << std::endl;
}