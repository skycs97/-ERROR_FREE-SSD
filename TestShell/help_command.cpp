#include "help_command.h"

void HelpCommand::run(const CommandRunner& cmdRunner) const
{
	FactoryCommand factory;
	for (const string& cmd : AVAILABLE_COMMAND_LIST) {
		std::cout << factory.makeCommand(cmd)->getHelp() << std::endl;;
	}

	std::cout << std::endl << std::endl;
	std::cout << "-------------------Developers-------------------------\n";
	for (const string& str : DEVELOPERS) {
		std::cout << str << ", ";
	}

	std::cout << std::endl;
}