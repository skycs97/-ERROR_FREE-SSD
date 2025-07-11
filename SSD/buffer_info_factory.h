#pragma once
#include "buffer_info.h"
#include "global_config.h"

class BufferInfoFactory {
public:
	std::shared_ptr<BufferInfo> createBuffer(const string& fileName);

	std::shared_ptr<BufferInfo> createWriteBuffer(int LBA, const string& data);
	std::shared_ptr<BufferInfo> createEraseBuffer(int LBA, int size);
	std::shared_ptr<BufferInfo> createEmptyBuffer();

	static BufferInfoFactory& getInstance() {
		static BufferInfoFactory instance;
		return instance;
	}
private:
	BufferInfoFactory() = default;
	BufferInfoFactory& operator=(const BufferInfoFactory& other) = delete;
	BufferInfoFactory(const BufferInfoFactory& other) = delete;
};