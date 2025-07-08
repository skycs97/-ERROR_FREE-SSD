#pragma once
#include "ssd_interface.h"
#include <vector>

using std::string;
using std::vector;

class CommandRunner {
public:
	string runCommand(vector<string> cmd);

	void setStorage(SsdInterface* ssdInterface);
private:
	SsdInterface* ssdInterface = nullptr;
};