#include <fstream>
#include "FileHandler.h"

using std::string;
using std::ofstream;
using std::ifstream;

void FileHandler::write(const string& file_name, const vector<string>& output_string) {
	ofstream writefile;
	writefile.open(file_name);
	for (const auto& line : output_string) {
		writefile << line << '\n';
	}
	writefile.close();
}

vector<string> FileHandler::read(const string& file_name) {
	ifstream readfile;
	readfile.open(file_name);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(readfile, line)) {
		lines.push_back(line);
	}
	readfile.close();
	return lines;
}