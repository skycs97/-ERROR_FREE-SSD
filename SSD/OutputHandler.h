#pragma once
#include <string>
#include "FileHandler.h"

using std::string;


class OutputHandler {
public:
	OutputHandler(FileHandler* fileHandler ) : fileHandler(fileHandler) {}

	void output(const string& output_string);
	string read(void);

private:
	FileHandler* fileHandler;
};
