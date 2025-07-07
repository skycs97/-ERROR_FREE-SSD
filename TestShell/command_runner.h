#pragma once
#include "storage.h"
#include <vector>

using std::string;
using std::vector;

class CommandRunner {
public:
	CommandRunner(Storage* storage);

	string runCommand(vector<string> cmd);
private:
	Storage* storage;
};