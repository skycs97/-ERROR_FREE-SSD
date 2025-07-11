#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class FileHandler {
public:
	// Path에 Directory 생성
	virtual void createDirectory(const string& path) = 0;

	// Path에 Empty File 생성
	virtual void createFile(const string& path) = 0;

	// Path에 있는 File Read 하여 포인터 반환
	virtual char* readFile(const string& path) = 0;
	
	// Path에 있는 파일에 Data 쓰기
	virtual void writeData(const string& path, const string& data) = 0;

	// old_name의 파일 이름 변경
	virtual void rename(const string& old_name, const string& new_name) const = 0;
	
	// Directory에서 file 이름의 len 만큼만 비교하여 같은 파일이 존재하는지 여부 반환
	virtual bool isFileExistByMatchLength(const string& dir_path, const string& file_name, size_t len) = 0;
	
	// Path에 있는 파일들 중에서 prefix가 포함되어 있는 파일명 반환
	virtual vector<string> getFileUsingPrefix(const string& path, const string& prefix) = 0;

private:

};