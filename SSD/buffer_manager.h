#pragma once
#include <string>
#include <vector>
#include <cstring>
#include <Windows.h>
#include <stdexcept>
#include "nand_flash_memory_impl.h"

using std::string;
using std::vector;

class BufferManager {
public:
	struct BufferInfo
	{
		string fname;
		CMD_TYPE cmd;
		int lba;
		string written_data;
		int erase_size;
	};

	BufferManager(NandFlashMemory* nandFlashMemory, FileHandler* fileHandler)
		: nandFlashMemory{ nandFlashMemory }, fileHandler{ fileHandler } {
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
	vector<BufferInfo> buffers{ BUFFER_SIZE };
	int valid_buf_cnt{ 0 };

	// Buffer 파일 존재 여부를 반환합니다.
	bool existBufferFile(int buf_idx);

	// Buffer Empty 파일을 생성합니다.
	void createBufferFile(int buf_idx);

	// Buffer 파일의 Prefix 매크로 반환합니다.
	const char* getBufferFilePrefix(int buf_idx);

	// 버퍼 상태 업데이트
	void updateBufferState(int buf_idx);

	void fillBufferInfo(string fname, int buf_idx, bool need_file_change);

	void setBufferInfo(
		int buf_idx,
		string fname,
		CMD_TYPE cmd,
		int lba,
		string written_data,
		int size
	);

	// 버퍼가 5개가 가득 찬 경우 true를 리턴합니다.
	bool isBufferFull();

	//fileHandler에 새로 버퍼를 기록합니다.
	void writeBuffer(const string& old_name, const string& new_name);

	void IncreaseBufferCnt();

	void DecreaseBufferCnt();
};