#pragma once
#include <cstring>
#include <Windows.h>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include "global_config.h"
#include "file_handler.h"

using std::ofstream;

class FileHandlerImpl : public FileHandler
{
public:
	FileHandlerImpl() = default;

	// Path에 Directory 생성
	void createDirectory(const string& path) override;

	// Path에 Empty File 생성
	void createFile(const string& path) override;

	// Path에 있는 File Read 하여 포인터 반환
	char* readFile(const string& path) override;

	// Path에 있는 파일에 Data 쓰기
	void writeData(const string& path, const string& data) override;

	// old_name의 파일 이름 변경
	void rename(const string& old_name, const string& new_name) const override;

	// Directory에서 file 이름의 len 만큼만 비교하여 같은 파일이 존재하는지 여부 반환
	bool isFileExistByMatchLength(const string& dir_path, const string& file_name, int len) override;

	// Path에 있는 파일들 중에서 prefix가 포함되어 있는 파일명 반환
	vector<string> getFileUsingPrefix(const string& path, const string& prefix) override;

private:

};



