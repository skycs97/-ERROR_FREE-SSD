#pragma once
#include <vector>
#include "ssd_interface.h"

using std::string;
using std::vector;

class CommandRunner {
public:
	string read(const string& LBA) const;
	string write(const string& LBA, const string& value) const;
	string erase(const string& startLBA, const string& LBARange) const;
	string flush() const;
	bool isSetSsdInterface() const;
	void setStorage(SsdInterface* ssdInterface);
private:
	SsdInterface* ssdInterface = nullptr;
	static const int MAX_ERASE_RANGE = 10;
};