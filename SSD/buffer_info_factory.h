#pragma once
#include "buffer_info.h"
#include "global_config.h"

class BufferInfoFactory {
public:
	BufferInfo* createCommand(const string& fileName);

	BufferInfo* createWriteCommand(int LBA, const string& data);
	BufferInfo* createEraseCommand(int LBA, int size);

	static BufferInfoFactory& getInstance() {
		static BufferInfoFactory instance;
		return instance;
	}
private:
	BufferInfoFactory() = default;
	BufferInfoFactory& operator=(const BufferInfoFactory& other) = delete;
	BufferInfoFactory(const BufferInfoFactory& other) = delete;
};