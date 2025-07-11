#pragma once
#include "buffer_info.h"
#include "global_config.h"

class BufferInfoFactory {
public:
	BufferInfo* createBuffer(const string& fileName);

	BufferInfo* createWriteBuffer(int LBA, const string& data);
	BufferInfo* createEraseBuffer(int LBA, int size);
	BufferInfo* createEmptyBuffer();

	static BufferInfoFactory& getInstance() {
		static BufferInfoFactory instance;
		return instance;
	}
private:
	BufferInfoFactory() = default;
	BufferInfoFactory& operator=(const BufferInfoFactory& other) = delete;
	BufferInfoFactory(const BufferInfoFactory& other) = delete;
};