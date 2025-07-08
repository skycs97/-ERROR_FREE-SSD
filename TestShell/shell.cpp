#include "shell.h"

void TestShell::runShell() {
	while (1) {
		string input;
		std::cout << "[SHELL] ";
		std::getline(std::cin, input);

		if (input == "")
			continue;

		try {
			command = parser.getCommand(input)->getShellCommands();
			if (command[0] == "exit")
				return;
			else if (command[0] == "help") {
				HelpCommand();
			}
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}

	}
}

void TestShell::HelpCommand() {

	std::cout << std::left << "Creator" << std::endl;
	std::cout << std::left << std::setw(15) << "skycs97"
		<< std::left << std::setw(15) << "dongs83"
		<< std::left << std::setw(15) << "iamsoonwonchoi" << std::endl;
	std::cout << std::left << std::setw(15) << "julysky123"
		<< std::left << std::setw(15) << "zeroexit-ryu"
		<< std::left << std::setw(15) << "JIeunAmy"
		<< std::left << std::setw(15) << "choo4r" << std::endl;

	std::cout << std::endl;
	std::cout << std::left << "Command" << std::endl;

	std::cout << std::left << std::setw(4) << ""
		<< std::left << std::setw(30) << "read [LBA]"
		<< std::left << std::setw(20) << "Specific index (LBA) read" << std::endl;

	std::cout << std::left << std::setw(4) << ""
		<< std::left << std::setw(30) << "fullread"
		<< std::left << std::setw(20) << "Total index (LBA) read" << std::endl;

	std::cout << std::left << std::setw(4) << ""
		<< std::left << std::setw(30) << "write [LBA] [Value]"
		<< std::left << std::setw(20) << "Specific index (LBA) write" << std::endl;

	std::cout << std::left << std::setw(4) << ""
		<< std::left << std::setw(30) << "fullwrite"
		<< std::left << std::setw(20) << "Total index (LBA) write" << std::endl;

	std::cout << std::left << std::setw(4) << ""
		<< std::left << std::setw(30) << "exit"
		<< std::left << std::setw(20) << "Program exit" << std::endl;

	std::cout << std::left << std::setw(4) << ""
		<< std::left << std::setw(30) << "help"
		<< std::left << std::setw(20) << "Program useage" << std::endl;

	std::cout << std::endl;
}