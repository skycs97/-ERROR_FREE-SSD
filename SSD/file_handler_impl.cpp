#include "file_handler_impl.h"

using std::string;
using std::ofstream;
using std::ifstream;

void FileHandlerImpl::createDirectory(const string& path)
{
	if (!(CreateDirectoryA(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS))
		throw std::runtime_error("Fail to create directory.");
}

void FileHandlerImpl::createFile(const string& path)
{
	std::ofstream outFile(path.c_str());
	if (!outFile.is_open()) {
		throw std::runtime_error("Failed to create file: " + path);
	}

	outFile << "";
	outFile.close();
}

char* FileHandlerImpl::readFile(const string& path)
{
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + path);
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	// 동적 메모리 할당
	char* buffer = new char[size + 1];  // +1 for null-terminator
	if (!file.read(buffer, size)) {
		delete[] buffer;
		throw std::runtime_error("Failed to read file: " + path);
	}

	buffer[size] = '\0';  // 문자열처럼 쓰고 싶을 경우

	return buffer;  // 호출자가 delete[]로 해제해야 함
}

void FileHandlerImpl::writeData(const string& path, const string& data)
{
	std::ofstream outFile(path.c_str());
	if (!outFile.is_open())
		throw std::runtime_error("Fail to open " NAND_FILENAME);

	outFile << data;
	if (outFile.fail())
		throw std::runtime_error("Fail to write data " NAND_FILENAME);

	outFile.close();
}

void FileHandlerImpl::rename(const string& old_name, const string& new_name) const
{
	if (std::rename(old_name.c_str(), new_name.c_str()) == 0) {
		return;
	}
	else {
		throw std::runtime_error("rename fail");
	}
}

bool FileHandlerImpl::isFileExistByMatchLength(const string& dir_path, const string& file_name, size_t len)
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

vector<string> FileHandlerImpl::getFileUsingPrefix(const string& path, const string& prefix)
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