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
	// todo: 파일 read 기능 필요시 구현
	return {};
}