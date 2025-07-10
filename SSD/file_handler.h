#pragma once
#include <string>
#include <cstring>
#include <Windows.h>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "global_config.h"

using std::ofstream;
using std::string;
using std::vector;

class FileHandler {
public:
	FileHandler() = default;

	virtual void write(const string& file_name, const vector<string>& output_string);
	virtual vector<string> read(const string& file_name);
	virtual void createEmptyFile(const string& file_path);
	virtual void rename(const string& old_name, const string& new_name) const;
	virtual vector<string> findFileUsingPrefix(const string& path, const string& prefix);


	bool createDirectory(const string& path);
	virtual bool createFile(const string& path);
	virtual bool writeData(const string& path, const string& data);
	char* readFile(const string& path, int& size);
	virtual bool isFileExistByMatchLength(const string& dir_path, const string& file_name, int len);
private:

};