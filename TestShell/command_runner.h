#pragma once
#include "storage.h"
#include <vector>

using std::string;
using std::vector;

class CommandRunner {
public:
	string runCommand(vector<string> cmd);

	void setStorage(Storage* storage);
private:
	Storage* storage;
};