#include <fstream>
#include <stdexcept>
#include <iomanip>
#include "file_handler.h"

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

void FileHandler::createEmptyFile(const string& file_path)
{
	std::ofstream outFile(file_path.c_str());
	if (!outFile) {
		throw std::exception("Fail to create buffer file.");
	}

	outFile << "";
	outFile.close();

	return;
}

void FileHandler::rename(const string& old_name, const string& new_name) const
{
	if (std::rename(old_name.c_str(), new_name.c_str()) == 0) {
		// success
		return;
	}
	else {
		throw std::runtime_error("rename fail");
	}
}

vector<string> FileHandler::findFileUsingPrefix(const string& path, const string& prefix)
{
	std::vector<std::string> matchingFiles;

	std::string searchPattern = path + "\\*";  // 모든 파일 탐색
	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::exception("Invalid path");
	}

	do {
		const char* fileName = findData.cFileName;

		// "." 또는 ".." 는 스킵
		if (strcmp(fileName, ".") == 0 || strcmp(fileName, "..") == 0) {
			continue;
		}

		// 파일 이름이 prefix로 시작하는지 확인
		if (strncmp(fileName, prefix.c_str(), prefix.length()) == 0) {
			matchingFiles.push_back(fileName);
		}

	} while (FindNextFileA(hFind, &findData) != 0);

	FindClose(hFind);
	return matchingFiles;
}

bool FileHandler::createDirectory(const string& path)
{
	if (!(CreateDirectoryA(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS)) return false;
	return true;
}

bool FileHandler::createFile(const string& path)
{
	std::ofstream outFile(path.c_str());
	if (!outFile.is_open()) {
		return false;
	}

	outFile << "";
	outFile.close();
	return true;
}

bool FileHandler::writeData(const string& path, const string& data)
{
	std::ofstream outFile(path.c_str());
	if (!outFile.is_open()) {
		return false;
		throw std::runtime_error("Failed to open file: " + path);
	}

	outFile << data;

	if (outFile.fail()) {
		return false;
		throw std::runtime_error("Failed to write to file: " + path);
	}

	outFile.close();
	return true;
}

char* FileHandler::readFile(const string& path, int& size)
{
	return nullptr;
}

bool FileHandler::isFileExistByMatchLength(const string& dir_path, const string& file_name, int len)
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(dir_path.c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::exception("Can't open buffer directory.");
	}

	bool found = false;
	do {
		if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (strncmp(findFileData.cFileName, file_name.c_str(), len) == 0) {
				found = true;
				break;
			}
		}
	} while (FindNextFileA(hFind, &findFileData));

	FindClose(hFind);

	return found;
}