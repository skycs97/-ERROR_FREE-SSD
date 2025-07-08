#pragma once
#include <string>
#include <fstream>
#include <vector>
using std::ofstream;
using std::string;
using std::vector;

class FileHandler {
public:
	FileHandler() {}

	virtual void write(const string& file_name, const vector<string>& output_string);
	virtual vector<string>& read(const string& file_name);

private:
	const string OUTPUT_FILENAME = "ssd_output.txt";
	ofstream file;
};