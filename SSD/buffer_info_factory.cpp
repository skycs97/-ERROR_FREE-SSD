#include "buffer_info_factory.h"
#include <regex>

std::shared_ptr<BufferInfo> BufferInfoFactory::createBuffer(const string& fname) {
	if (std::regex_match(fname, WriteBufferInfo::fileNameRegex)) {
		return std::make_shared<WriteBufferInfo>(fname);
	}
	else if (std::regex_match(fname, EraseBufferInfo::fileNameRegex)) {
		return std::make_shared<EraseBufferInfo>(fname);
	}
	return std::make_shared<EmptyBufferInfo>();
}

std::shared_ptr<BufferInfo> BufferInfoFactory::createWriteBuffer(int LBA, const string& data) {
	return std::make_shared<WriteBufferInfo>(LBA, data);
}
std::shared_ptr<BufferInfo> BufferInfoFactory::createEraseBuffer(int LBA, int size) {
	return std::make_shared<EraseBufferInfo>(LBA, size);
}
std::shared_ptr<BufferInfo> BufferInfoFactory::createEmptyBuffer() {
	return std::make_shared<EmptyBufferInfo>();
}