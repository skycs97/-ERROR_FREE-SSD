#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class NandFlashMemory {
public:
	virtual void init() = 0;
	virtual vector<string> read() = 0;
	virtual string write(vector<string>& data) = 0;
};