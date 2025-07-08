#include "shell.h"

void TestShell::runShell() {
	string input;

	while (1) {
		input = getUserInput();
		if (isEmptyInput(input))
			continue;

		try {
			command = parser.getCommand(input);
			command->run();
		}
		catch (std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}

	}
}

string TestShell::getUserInput() {
	string input;
	std::cout << "[SHELL] ";
	std::getline(std::cin, input);
	return input;
}

bool TestShell::isEmptyInput(const string& input) {
	return (input == "");
}