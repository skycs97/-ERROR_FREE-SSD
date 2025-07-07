#pragma once
#include <string>

using std::string;

class NandFlashMemory {
public:
	virtual string read(int LBA) = 0;
	virtual string write(int lba, int data) = 0;
};