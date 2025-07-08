#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class NandFlashMemory {
public:
	virtual vector<string> read() = 0;
	virtual string write(int lba, int data) = 0;
};