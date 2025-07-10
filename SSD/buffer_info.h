#pragma once
#include <regex>
#include <string>
#include <vector>
#include "global_config.h"
using std::string;
using std::vector;

struct InternalBufferInfo {
	CMD_TYPE cmd;
	string data;
};

class BufferInfo
{
public:
	virtual string getFileName(int bufIndex) = 0;
	virtual void updateInternalBufferInfos(vector<InternalBufferInfo>&) = 0;
};

class WriteBufferInfo : public BufferInfo {
public:
	static const std::regex fileNameRegex;
	WriteBufferInfo(int lba, const string& data) :lba{ lba }, written_data(data) {}
	WriteBufferInfo(const string& fname) {
		std::smatch m;
		std::regex_search(fname, m, WriteBufferInfo::fileNameRegex);
		lba = std::atoi(m.str(1).c_str());
		written_data = m.str(2);
	}
	string getFileName(int bufIndex) override;
	void updateInternalBufferInfos(vector<InternalBufferInfo>&) override;
private:
	string written_data;
	int lba;
};

class EraseBufferInfo : public BufferInfo {
public:
	static const std::regex fileNameRegex;
	EraseBufferInfo(int lba, int size) : lba{ lba }, size(size) {}
	EraseBufferInfo(const string& fname) {
		std::smatch m;
		std::regex_search(fname, m, EraseBufferInfo::fileNameRegex);
		lba = std::atoi(m.str(1).c_str())/*LBA*/;
		size = std::atoi(m.str(2).c_str())/*erase size*/;
	}
	string getFileName(int bufIndex) override;
	void updateInternalBufferInfos(vector<InternalBufferInfo>&) override;
private:
	int size;
	int lba;
};

class EmptyBufferInfo : public BufferInfo {
public:
	EmptyBufferInfo() {}
	string getFileName(int bufIndex) override;
	void updateInternalBufferInfos(vector<InternalBufferInfo>&) override;
};

