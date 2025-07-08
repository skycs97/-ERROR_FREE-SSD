#pragma once
#include "ssd_interface.h"
#include <vector>

using std::string;
using std::vector;

class CommandRunner {
public:
	string read(const string& LBA);
	string write(const string& LBA, const string& value);
	void setStorage(SsdInterface* ssdInterface);
private:
	SsdInterface* ssdInterface = nullptr;
};