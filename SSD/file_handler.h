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
	
	// Path에 있는 File Read 하여 포인터 반환
	virtual char* readFile(const string& path);

	// Path에 Directory 생성
	void createDirectory(const string& path);
	
	// Path에 Empty File 생성
	virtual void createFile(const string& path);
	
	// Path에 있는 파일에 Data 쓰기
	virtual void writeData(const string& path, const string& data);
	
	virtual bool isFileExistByMatchLength(const string& dir_path, const string& file_name, int len);
	
	// old_name의 파일 이름 변경
	virtual void rename(const string& old_name, const string& new_name) const;
	
	// Path에 있는 파일들 중에서 prefix가 포함되어 있는 파일명 반환
	virtual vector<string> getFileUsingPrefix(const string& path, const string& prefix);

private:

};