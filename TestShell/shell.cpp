#include "shell.h"
#include "ssd_impl.h"

void TestShell::runShell(int argc, char* argv[]) {

	if (isRunShellScript(argc) == true) {
		string filePath = argv[1];
		runShellScript(filePath);
		return;
	}

	startShellLoop();
}

void TestShell::startShellLoop()
{
	string input;

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
		runShellCommand(command);
	}
	catch (std::exception& e) {
		printTestResult(e.what());
		result = false;
	}

	return result;
}

void TestShell::runShellCommand(std::shared_ptr<Command> command)
{
	command->run(runner);
}

TestShell::TestShell() {
	runner.setStorage(new SsdImpl());

}