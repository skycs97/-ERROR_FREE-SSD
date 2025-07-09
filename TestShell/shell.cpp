#include "shell.h"

void TestShell::runShell(int argc, char* argv[]) {
	string input;

	if (isRunShellScript(argc) == true) {
		string filePath = argv[1];
		runShellScript(filePath);
		return;
	}

	while (1) {
		input = getUserInput();
		if (isEmptyInput(input))
			continue;

		parseAndRunCommand(input);
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

bool TestShell::isRunShellScript(int argc) {
	return (argc == 2);
}

void TestShell::runShellScript(const string& filename) {
	ifstream  inputFile(filename);

	if (isFileOpenFail(inputFile)) {
		std::cout << "Error: could not open file " << filename << std::endl;
		return;
	}

	string input;
	while (getline(inputFile, input)) {
		if (isEmptyInput(input))
			break;

		if (parseAndRunCommand(input) == false) {
			break;
		}
	}

	inputFile.close();
	return;
}

bool TestShell::isFileOpenFail(const ifstream& inputFile)
{
	return !(inputFile.is_open());
}

void TestShell::printTestResult(const string& result)
{
	std::cout << result << std::endl;
}

bool TestShell::parseAndRunCommand(const string& input) {
	bool result = true;
	try {
		auto command = parser.parseAndMakeShellCommand(input);
		command->run(runner);
	}
	catch (TestScriptFailExcpetion& e) {
		printTestResult(e.what());
		result = false;
	}

	return result;
}