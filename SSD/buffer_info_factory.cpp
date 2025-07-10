#include "buffer_info_factory.h"
#include <regex>

BufferInfo* BufferInfoFactory::createCommand(const string& fname) {
	if (std::regex_match(fname, WriteBufferInfo::fileNameRegex)) {
		return new WriteBufferInfo(fname);
	}
	else if (std::regex_match(fname, EraseBufferInfo::fileNameRegex)) {
		return new EraseBufferInfo(fname);
	}
	return new EmptyBufferInfo();
}
