#pragma once
#include <string>
#include <fstream>

using std::ofstream;
using std::string;

class FileHandler {
public:
	FileHandler() {}

	virtual void write(const string& output_string);
	virtual string read();

private:
	const string OUTPUT_FILENAME = "ssd_output.txt";
	ofstream file;
};