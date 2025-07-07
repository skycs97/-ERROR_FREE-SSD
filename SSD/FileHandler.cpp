#include <fstream>
#include "FileHandler.h"

using std::string;
using std::ofstream;
using std::ifstream;

void FileHandler::write(const string& output_string) {
	file.open(OUTPUT_FILENAME);
	file << output_string;
	file.close();
}

string FileHandler::read(void) {
	ifstream readfile;
	readfile.open(OUTPUT_FILENAME);
	string output_string;
	readfile >> output_string;
	readfile.close();

	return output_string;
}