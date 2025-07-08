#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "command.h"
#include "command_runner.h"

Command::Command(std::vector<std::string> commands) : ShellCommands(commands)
{
}

std::vector<std::string> Command::getShellCommands(void) {
	return ShellCommands;
}

std::string Command::getHelp(void) const {
	return help;
}

int Command::getNumOfArgs(void) {
	return numOfArgs;
}

void ReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.read(ShellCommands[1]));
}

void WriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	result.push_back(cmdRunner.write(ShellCommands[1], ShellCommands[2]));
}

void ExitCommand::run(const CommandRunner& cmdRunner) const
{
	exit(0);
}

void HelpCommand::run(const CommandRunner& cmdRunner) const
{
	std::cout << getHelp();
}

void FullWriteCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_ADDR; lba <= MAX_ADDR; lba++) {
		result.push_back(cmdRunner.write(std::to_string(lba), ShellCommands[1]));
	}
}

void FullReadCommand::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	for (int lba = MIN_ADDR; lba <= MAX_ADDR; lba++) {
		result.push_back(cmdRunner.read(std::to_string(lba)));
	}
}
void FullWriteAndReadCompare::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	int lba = 0;
	int testSize = 5;
	std::vector<string> testValue = { "0xA5A5A5A5", "0x5A5A5A5A", "0xFFFFFFFF", "0xF0F0F0F0", "0x0F0F0F0F" };
	string writeSuccess = "";
	string res;

	while (lba <= MAX_ADDR) {
		for (int i = 0; i < testSize; i++) {
			if (writeSuccess == (res = cmdRunner.write(std::to_string(lba + i), testValue[0])))
				continue;
			result.push_back(res);
		}

		for (int i = 0; i < testSize; i++) {
			if (testValue[0] == (res = cmdRunner.read(std::to_string(lba + i))))
				continue;
			result.push_back(res);
		}

		lba += testSize;

		for (int i = 0; i < testSize; i++) {
			if (writeSuccess == (res = cmdRunner.write(std::to_string(lba + i), testValue[i])))
				continue;
			result.push_back(res);
		}

		for (int i = 0; i < testSize; i++) {
			if (testValue[i] == (res = cmdRunner.read(std::to_string(lba + i))))
				continue;
			result.push_back(res);
		}

		lba += testSize;
	}

	if (result.size())
		std::cout << "FullWriteAndReadCompare Fail" << std::endl;
	else
		std::cout << "FullWriteAndReadCompare Pass" << std::endl;
}

void PartialLBAWrite::run(const CommandRunner& cmdRunner) const
{
	for (int testRepeat = 0; testRepeat < REPEAT_COUNT; testRepeat++) {
		vector<std::string> result;

		for (std::string Lba : TestLbaList) {
			cmdRunner.write(Lba, WRITE_DATA);
		}

		for (std::string Lba : TestLbaList) {

			result.push_back(cmdRunner.read(Lba));
		}

		if (checkResult(result) == false) {
			std::cout << "FAIL\n";
		}
	}
	std::cout << "PASS\n";
}

bool PartialLBAWrite::checkResult(const vector<std::string>& result) const
{
	string firstItem = result[0];

	for (const std::string& resultitem : result)
	{
		if (resultitem != firstItem) { return false; }
	}
	return true;
}

void WriteReadAging::run(const CommandRunner& cmdRunner) const
{
}

Command* FactoryCommand::makeCommand(const std::string& cmd)
{
	std::istringstream ss(cmd);
	std::string word;
	std::vector<std::string> commands;
	std::string shellCmd;

	while (ss >> word) {
		commands.push_back(word);
	}

	shellCmd = commands.front();

	if (shellCmd == CMD_READ) return new ReadCommand(commands);
	else if (shellCmd == CMD_WRITE) return new WriteCommand(commands);
	else if (shellCmd == CMD_EXIT) return new ExitCommand(commands);
	else if (shellCmd == CMD_HELP) return new HelpCommand(commands);
	else if (shellCmd == CMD_FULLWRITE) return new FullWriteCommand(commands);
	else if (shellCmd == CMD_FULLREAD) return new FullReadCommand(commands);
	else if (shellCmd == CMD_1_ || shellCmd == CMD_1_FULLWRITEANDREADCOMPARE) return new FullWriteAndReadCompare(commands);

	else if ((shellCmd == CMD_2_PartialLBAWrite) || (shellCmd == CMD_2_)) return new PartialLBAWrite(commands);

	else return nullptr;
}