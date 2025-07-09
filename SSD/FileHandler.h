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
	FileHandler();

	void init();
	virtual bool checkExistNandFile(const string& file_name);
	virtual void createInitNandFile(const string& file_name);
	virtual void write(const string& file_name, const vector<string>& output_string);
	virtual vector<string> read(const string& file_name);

	void createDirIfNotExist(const string& dir_path);
	bool isExist(const string& dir_path, const string& file_name);
	void createEmptyFile(const string& file_path);

private:

};