#pragma once

#include <string>
#include <fstream>

using std::string;
using std::ofstream;

class OutputHandler {
public:
	OutputHandler() {}

	virtual void output(const string& output_string);

private:
	const string OUTPUT_FILENAME = "ssd_output.txt";
	ofstream file;
};