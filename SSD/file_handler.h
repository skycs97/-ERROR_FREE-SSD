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
	
	// Path�� �ִ� File Read �Ͽ� ������ ��ȯ
	virtual char* readFile(const string& path);

	// Path�� Directory ����
	void createDirectory(const string& path);
	
	// Path�� Empty File ����
	virtual void createFile(const string& path);
	
	// Path�� �ִ� ���Ͽ� Data ����
	virtual void writeData(const string& path, const string& data);
	
	virtual bool isFileExistByMatchLength(const string& dir_path, const string& file_name, int len);
	
	// old_name�� ���� �̸� ����
	virtual void rename(const string& old_name, const string& new_name) const;
	
	// Path�� �ִ� ���ϵ� �߿��� prefix�� ���ԵǾ� �ִ� ���ϸ� ��ȯ
	virtual vector<string> getFileUsingPrefix(const string& path, const string& prefix);

private:

};