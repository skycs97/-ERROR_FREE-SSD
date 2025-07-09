#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "gmock/gmock.h"
#include "logger.h"

namespace {
	const std::string TEST_LOG_FILE = "latest.log";
}

class LoggerTest : public ::testing::Test {
protected:
	std::string readLogFile() {
		std::ifstream file(TEST_LOG_FILE);
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	int getNumOfFiles(const std::string& prefix, const std::string& extension) {
		WIN32_FIND_DATAA findData;
		std::string searchPattern = prefix + "*" + extension;

		int count = 0;
		HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findData);
		if (hFind == INVALID_HANDLE_VALUE) {
			return 0;
		}

		do {
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				++count;
			}
		} while (FindNextFileA(hFind, &findData));

		FindClose(hFind);
		return count;
	}

	std::vector<std::string> getFilename(const std::string& prefix, const std::string& extension) {
		std::vector<std::string> files;
		std::string searchPattern = prefix + "*" + extension;

		WIN32_FIND_DATAA findData;
		HANDLE hFind = FindFirstFileA(searchPattern.c_str(), &findData);

		if (hFind == INVALID_HANDLE_VALUE) {
			return files;
		}

		do {
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				files.push_back(findData.cFileName);
			}
		} while (FindNextFileA(hFind, &findData));

		FindClose(hFind);
		return files;
	}

	void logUntilMaxsize() {
		int curSize = logger.getLogFileSize();
		int prevSize = 0;

		while (curSize > prevSize) {
			logger.print(__func__, __TIMESTAMP__);

			prevSize = curSize;
			curSize = logger.getLogFileSize();
		}
	}
};

TEST_F(LoggerTest, AppendLogToExistingFile) {

	std::string before = readLogFile();

	logger.print(__func__, __DATE__);

	std::string after = readLogFile();

	EXPECT_GT(after.size(), before.size());

	EXPECT_NE(after.find(__func__), std::string::npos);
	EXPECT_NE(after.find(__DATE__), std::string::npos);
}

TEST_F(LoggerTest, AppendLogsToExistingFile) {

	std::string before = readLogFile();

	logger.print(__func__, __DATE__);
	logger.print(__func__, __DATE__);
	logger.print(__func__, __DATE__);

	std::string after = readLogFile();

	EXPECT_GT(after.size(), before.size());

	EXPECT_NE(after.find(__func__), std::string::npos);
	EXPECT_NE(after.find(__DATE__), std::string::npos);
	EXPECT_NE(after.find(__func__), std::string::npos);
	EXPECT_NE(after.find(__DATE__), std::string::npos);
	EXPECT_NE(after.find(__func__), std::string::npos);
	EXPECT_NE(after.find(__DATE__), std::string::npos);
}

//Default : DISABLE
TEST_F(LoggerTest, DISABLED_AppendLogsOver10KB) {

	int numOfUntilLogfiles = getNumOfFiles("until_", ".log");
	int numOfZipLogfiles = getNumOfFiles("until_", ".zip");
	std::vector<std::string> files = getFilename("until_", ".log");

	int expect_until, expect_zip;

	expect_until = 1;
	expect_zip = (numOfUntilLogfiles > 0) ? numOfZipLogfiles + 1 : 0;

	logUntilMaxsize();

	EXPECT_EQ(expect_until, getNumOfFiles("until_", ".log"));
	EXPECT_EQ(expect_zip, getNumOfFiles("until_", ".zip"));
}

//Default : DISABLE
TEST_F(LoggerTest, DISABLED_AppendLogsOver30KB) {

	int numOfUntilLogfiles = getNumOfFiles("until_", ".log");
	int numOfZipLogfiles = getNumOfFiles("until_", ".zip");
	std::vector<std::string> files = getFilename("until_", ".log");

	int expect_until, expect_zip;

	expect_until = 1;
	expect_zip = (numOfUntilLogfiles > 0) ? numOfZipLogfiles + 3 : numOfZipLogfiles + 2;

	logUntilMaxsize();
	logUntilMaxsize();
	logUntilMaxsize();

	EXPECT_EQ(expect_until, getNumOfFiles("until_", ".log"));
	EXPECT_EQ(expect_zip, getNumOfFiles("until_", ".zip"));
}