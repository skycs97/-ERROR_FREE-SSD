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

	// Path�� Directory ����
	void createDirectory(const string& path) override;

	// Path�� Empty File ����
	void createFile(const string& path) override;

	// Path�� �ִ� File Read �Ͽ� ������ ��ȯ
	char* readFile(const string& path) override;

	// Path�� �ִ� ���Ͽ� Data ����
	void writeData(const string& path, const string& data) override;

	// old_name�� ���� �̸� ����
	void rename(const string& old_name, const string& new_name) const override;

	// Directory���� file �̸��� len ��ŭ�� ���Ͽ� ���� ������ �����ϴ��� ���� ��ȯ
	bool isFileExistByMatchLength(const string& dir_path, const string& file_name, int len) override;

	// Path�� �ִ� ���ϵ� �߿��� prefix�� ���ԵǾ� �ִ� ���ϸ� ��ȯ
	vector<string> getFileUsingPrefix(const string& path, const string& prefix) override;

private:

};



