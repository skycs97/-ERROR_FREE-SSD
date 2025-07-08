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
	const string OUTPUT_FILENAME = "ssd_output.txt";
	FileHandler* fileHandler;
};
