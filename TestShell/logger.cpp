
#include "logger.h"

void Logger::print(const std::string& functionName, const std::string& message) {

	checkRenameFIles();

	std::string timestamp = getCurrentTimestamp();
	logFile << "[" << timestamp << "] "
		<< std::left << std::setw(16) << functionName
		<< ": " << message << std::endl;
}
std::size_t Logger::getLogFileSize() {
	std::ifstream file(LOGFILE_NAME, std::ios::binary);
	if (!file.is_open()) return 0;

	file.seekg(0, std::ios::end);
	return static_cast<std::size_t>(file.tellg());
}

Logger::Logger() {
	openLogFile();
}

Logger::~Logger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}

void Logger::openLogFile() {
	logFile.open(logFileName, std::ios::app);
	if (!logFile.is_open()) {
		throw std::runtime_error("Cannot open " + LOGFILE_NAME);
	}
}

std::string Logger::getCurrentTimestamp() {
	auto now = std::chrono::system_clock::now();
	std::time_t nowT = std::chrono::system_clock::to_time_t(now);
	std::tm timeInfo;
	localtime_s(&timeInfo, &nowT);

	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "%y.%m.%d %H:%M", &timeInfo);
	return std::string(buffer);
}

std::string Logger::getFileTimeForName() {
	auto now = std::chrono::system_clock::now();
	std::time_t nowTimeT = std::chrono::system_clock::to_time_t(now);
	std::tm timeInfo;
	localtime_s(&timeInfo, &nowTimeT);

	char buffer[30];
	std::strftime(buffer, sizeof(buffer), "%y%m%d_%H_%M_%S", &timeInfo);
	return std::string(buffer);
}

void Logger::renamePreviousLogFiles() {
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(LOGFILE_SEARCH_PATTERN.c_str(), &findFileData);
	int tryCnt = 0;

	if (hFind == INVALID_HANDLE_VALUE)
		return;

	do {
		std::string oldName = findFileData.cFileName;

		std::string baseName = oldName.substr(0, oldName.find_last_of('.'));
		std::string newName = baseName + LOGFILE_ZIP_EXTENSION;

		while (!MoveFileA(oldName.c_str(), newName.c_str())) {
			newName = baseName + "_" + LOGFILE_ZIP_EXTENSION;
			baseName += "(2)";

			if (tryCnt++ > 3)
				break;
		}

	} while (FindNextFileA(hFind, &findFileData) != 0);
	FindClose(hFind);
}

void Logger::checkRenameFIles() {
	if (getLogFileSize() < maxFileSize) return;

	logFile.close();

	renamePreviousLogFiles();

	std::string newName = LOGFILE_PREFIX + getFileTimeForName() + LOGFILE_EXTENSION;
	MoveFileA(logFileName.c_str(), newName.c_str());

	openLogFile();
}
