#pragma once
#include <string>
#include "nand_flash_memory_impl.h"
using std::string;
class BufferManager {
public:
	BufferManager(NandFlashMemory* nandFlashMemory, FileHandler* fileHandler)
		: nandFlashMemory{ nandFlashMemory }, fileHandler{ fileHandler } {
	}

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
private:
	NandFlashMemory* nandFlashMemory;
	FileHandler* fileHandler;

	//버퍼가 5개가 가득 찬 경우 true를 리턴합니다.
	bool isBufferFull();

	//fileHandler를 통해 버퍼를 업데이트 합니다.
	void updateBuffer();
};