#pragma once
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <vector>
#define logger Logger::getInstance()

namespace {
	const std::string LOGFILE_PREFIX = "until_";
	const std::string LOGFILE_EXTENSION = ".log";
	const std::string LOGFILE_ZIP_EXTENSION = ".zip";
	const std::string LOGFILE_NAME = "latest" + LOGFILE_EXTENSION;
	const int LOGFILE_MAXSIZE = 10 * 1024;
	const std::string LOGFILE_SEARCH_PATTERN = LOGFILE_PREFIX + "*" + LOGFILE_EXTENSION;
}

class Logger {
public:
	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}

	void print(const std::string& functionName, const std::string& message);
	std::size_t getLogFileSize();

private:
	Logger();
	~Logger();

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::ofstream logFile;
	const std::string logFileName = LOGFILE_NAME;
	const std::size_t maxFileSize = LOGFILE_MAXSIZE;

	void openLogFile();
	std::string getCurrentTimestamp();
	std::string getFileTimeForName();
	void renamePreviousLogFiles();
	void checkRenameFIles();
};