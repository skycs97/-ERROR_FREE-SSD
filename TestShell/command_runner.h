#pragma once
#include "ssd_interface.h"
#include <vector>

using std::string;
using std::vector;

class CommandRunner {
public:
	string read(const string& LBA) const;
	string write(const string& LBA, const string& value) const;
	bool isSetSsdInterface() const;
	void setStorage(SsdInterface* ssdInterface);
private:
	SsdInterface* ssdInterface = nullptr;
};