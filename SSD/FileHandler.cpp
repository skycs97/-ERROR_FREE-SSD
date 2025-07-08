#include <fstream>
#include <stdexcept>
#include <iomanip>
#include "FileHandler.h"

using std::string;
using std::ofstream;
using std::ifstream;

FileHandler::FileHandler()
{
	
}

void FileHandler::init()
{
	if (checkExistNandFile(NAND_FILENAME) == false)
	{
		createInitNandFile(NAND_FILENAME);
	}
}

bool FileHandler::checkExistNandFile(const string& file_name)
{
	ifstream readfile;
	readfile.open(file_name);
	return !(readfile.fail());
}

void FileHandler::createInitNandFile(const string& file_name)
{
	ofstream outfile(file_name);

	if (!outfile.is_open()) {
		throw std::exception("Fail to create ssd_nand.txt");
	}

	for (int i = MIN_LBA; i <= MAX_LBA; ++i) {
		outfile << std::setw(2) << std::setfill('0') << std::dec << i << '\t'
			<< "0x"
			<< std::setw(8) << std::setfill('0') << std::hex << std::uppercase << 0
			<< '\n';
	}

	outfile.close();
	return;
}

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