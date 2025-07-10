#pragma once
#include <string>
#include <vector>
#include <regex>
#include <cstring>
#include <Windows.h>
#include <stdexcept>
#include "nand_flash_memory_impl.h"

using std::string;
using std::vector;

struct InternalBufferInfo {
	CMD_TYPE cmd;
	string data;
};

class BufferInfo
{
protected:
public:

	virtual string getFileName(int bufIndex) = 0;
	virtual void updateInternalBufferInfos(vector<InternalBufferInfo>) = 0;
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
	void updateInternalBufferInfos(vector<InternalBufferInfo>) override;
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
	void updateInternalBufferInfos(vector<InternalBufferInfo>) override;
	int size;
	int lba;
};

class EmptyBufferInfo : public BufferInfo {
public:
	EmptyBufferInfo(){}
	string getFileName(int bufIndex) override;
	void updateInternalBufferInfos(vector<InternalBufferInfo>) override;
};


class BufferManager {
public:

	BufferManager(NandFlashMemory* nandFlashMemory, FileHandler* fileHandler)
		: nandFlashMemory{ nandFlashMemory }, fileHandler{ fileHandler } {

		flushInternalBuffers();

		for (int i = 0; i < BUFFER_SIZE; i++) {
			buffers[i] = new EmptyBufferInfo();
		}
	}

	void init();

	// lba 데이터가 버퍼에 없으면 false 를 리턴하고, 
	// 있으면 outputData에 데이터를 담고 true를 리턴합니다.
	bool read(int lba, string& outputData);

	// write 커맨드에 대한 내용을 버퍼에 씁니다.
	// 만일 버퍼가 가득차면 flush 수행 후에 버퍼에 씁니다.
	void addWriteCommand(int lba, const string& data);

	// erase 커맨드에 대한 내용을 버퍼에 씁니다.
	// 만일 버퍼가 가득차면 flush 수행 후에 버퍼에 씁니다.
	void addEraseCommand(int lba, int count);
	// 모든 버퍼의 내용을 nand에 기록합니다.
	void flush();


	// empty가 아닌 버퍼의 개수를 리턴합니다.
	int getUsedBufferCount();
private:
	NandFlashMemory* nandFlashMemory;
	FileHandler* fileHandler;
	vector<BufferInfo*> buffers{ BUFFER_SIZE };
	vector<InternalBufferInfo> internalBuffers{ 100 };
	int valid_buf_cnt{ 0 };

	// init step
	bool existBufferFile(int bufIndex);
	void createEmptyBufferFile(int bufIndex);
	string getBufferFilePrefix(int bufIndex);
	void updateBufferState(int bufIndex);
	void updateInternalBufferState();
	void fillBufferInfo(string fname, int bufIndex);
	CMD_TYPE getBufferTypeFromFilenames(const string& fname);
	void IncreaseBufferCnt();

	bool isBufferFull();
	void flushInternalBuffers();

	void writeBufferFile(const string& old_name, const string& new_name);
	void updateBufferByInternalBuffer();
	int createWriteBuffer(const string& internalBuffer, int bufIndex, int internalBufferIdx);
	int createEraseBufferAndPassedWriteBuffer(int eraseStartLBA, int eraseCount, int bufIndex, std::vector<int>& writeLBAs);
	vector<string> getOldFileNames();

	void setInternalBufferWrite(int lba, const std::string& data);
	void SetInternalBufferErase(int lba, int count);
	void WriteUpdatedBufferFiles();
	void writeEmptyBufferFiles();
	void fillEmptyBuffers();
	void writeAllBufferFiles(std::vector<std::string>& old_names);
	void updateNandData(std::vector<std::string>& datas);
};