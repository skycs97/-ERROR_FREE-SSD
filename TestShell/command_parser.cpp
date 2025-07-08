#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "command_parser.h"

using std::string;

std::vector<std::string> CommandParser::getCommand(const std::string& command)
{
	//Split cmdline
	std::vector<std::string> in;
	std::vector<std::string> out;
	std::istringstream ss(command);
	std::string word;

	while (ss >> word) {
		in.push_back(word);
	}

	//Handle command
	if (in[0] == "read") {
		if (in.size() != 2) {
			throw std::invalid_argument("Invalid argument");
		}

		int address = std::stoi(in[1]);
		if (address < 0 || address > 99) {
			throw std::invalid_argument("Out of range");
		}
		out.push_back("./ssd.exe");
		out.push_back("R");
		out.push_back(in[1]);
	}
	else if (in[0] == "write") {
		if (in.size() != 3) {
			throw std::invalid_argument("Invalid argument");
		}

		int address = std::stoi(in[1]);
		if (address < 0 || address > 99) {
			throw std::invalid_argument("Out of range");
		}

		out.push_back("./ssd.exe");
		out.push_back("W");
		out.push_back(in[1]);
		out.push_back(in[2]);
	}
	else if (in[0] == "exit") {
		if (in.size() != 1) {
			throw std::invalid_argument("Invalid argument");
		}

		out.push_back(in[0]);
	}
	else if (in[0] == "help") {
		if (in.size() != 1) {
			throw std::invalid_argument("Invalid argument");
		}
		out.push_back(in[0]);

		//print help
		//std::cout << "read" << "address" << std::endl;

	}
	else {
		throw std::invalid_argument("Invalid command");
	}
	return out;
}
