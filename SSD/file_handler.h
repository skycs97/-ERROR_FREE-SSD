#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

class FileHandler {
public:
	// Path�� Directory ����
	virtual void createDirectory(const string& path) = 0;

	// Path�� Empty File ����
	virtual void createFile(const string& path) = 0;

	// Path�� �ִ� File Read �Ͽ� ������ ��ȯ
	virtual char* readFile(const string& path) = 0;
	
	// Path�� �ִ� ���Ͽ� Data ����
	virtual void writeData(const string& path, const string& data) = 0;

	// old_name�� ���� �̸� ����
	virtual void rename(const string& old_name, const string& new_name) const = 0;
	
	// Directory���� file �̸��� len ��ŭ�� ���Ͽ� ���� ������ �����ϴ��� ���� ��ȯ
	virtual bool isFileExistByMatchLength(const string& dir_path, const string& file_name, size_t len) = 0;
	
	// Path�� �ִ� ���ϵ� �߿��� prefix�� ���ԵǾ� �ִ� ���ϸ� ��ȯ
	virtual vector<string> getFileUsingPrefix(const string& path, const string& prefix) = 0;

private:

};