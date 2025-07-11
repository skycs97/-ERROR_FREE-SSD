#pragma once
#include <string>
#include <vector>
#include <cstring>
#include <Windows.h>
#include <stdexcept>
#include "buffer_info.h"
#include "nand_flash_memory_impl.h"
#include "buffer_info_factory.h"

using std::string;
using std::vector;

class BufferManager {
public:

	BufferManager(NandFlashMemory* nandFlashMemory, FileHandler* fileHandler)
		: nandFlashMemory{ nandFlashMemory }, fileHandler{ fileHandler } {

		flushInternalBuffers();

		for (int i = 0; i < BUFFER_SIZE; i++) {
			buffers[i] = BufferInfoFactory::getInstance().createEmptyCommand();
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
	int validBufCount{ 0 };

	bool existEmptyBufferFile(int bufIndex);
	bool existNonEmptyBufferFile(int bufIndex);
	void createEmptyBufferFileAndUpdateState(int bufIndex);
	void updateBufferState(int bufIndex);
	string getBufferFilePrefix(int bufIndex);
	void fillBufferInfo(string fname, int bufIndex);
	void IncreaseBufferCnt();
	void updateInternalBufferState();

	bool IsDataInBuffer(int lba);
	bool isDataEmpty(const string& data);
	bool isBufferFull();

	void setInternalBufferWrite(int lba, const std::string& data);
	void SetInternalBufferErase(int lba, int count);

	void updateBufferFiles();
	void writeAllBufferFiles(std::vector<std::string>& old_names);
	void writeBufferFile(const string& old_name, const string& new_name);
	
	void updateNandData(std::vector<std::string>& datas);
	void flushInternalBuffers();
	void updateBufferFilesAllEmpty();
	void resetValidBufCount();

	vector<string> getOldFileNames();

	void updateBufferByInternalBuffer();
	int createWriteBuffer(int bufIndex, int LBA, const string& data);
	int createEraseBufferAndPassedWriteBuffer(int eraseStartLBA, int eraseCount, int bufIndex, std::vector<int>& writeLBAs);
	inline bool isLastLBA(int lba) { return lba == MAX_LBA; }
	
	void fillEmptyBuffers();
	
};