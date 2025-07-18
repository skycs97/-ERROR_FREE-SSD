#pragma once
#include <string>
#include "file_handler.h"
#include "global_config.h"

using std::string;


class OutputHandler {
public:
	OutputHandler(FileHandler* fileHandler) : fileHandler(fileHandler) {}

	void init();
	void output(const string& output_string);
	string read(void);
	FileHandler* getFileHandler() { return fileHandler; }

private:
	FileHandler* fileHandler;
};
