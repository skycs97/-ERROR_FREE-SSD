#include "buffer_info_factory.h"
#include <regex>

BufferInfo* BufferInfoFactory::createBuffer(const string& fname) {
	if (std::regex_match(fname, WriteBufferInfo::fileNameRegex)) {
		return new WriteBufferInfo(fname);
	}
	else if (std::regex_match(fname, EraseBufferInfo::fileNameRegex)) {
		return new EraseBufferInfo(fname);
	}
	return new EmptyBufferInfo();
}

BufferInfo* BufferInfoFactory::createWriteBuffer(int LBA, const string& data) {
	return new WriteBufferInfo(LBA, data);
}
BufferInfo* BufferInfoFactory::createEraseBuffer(int LBA, int size) {
	return new EraseBufferInfo(LBA, size);
}
BufferInfo* BufferInfoFactory::createEmptyBuffer() {
	return new EmptyBufferInfo();
}