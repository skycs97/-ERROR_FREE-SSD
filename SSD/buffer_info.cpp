#include <regex>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "buffer_info.h"
#include "global_config.h"

using std::string;
using std::vector;

const std::regex WriteBufferInfo::fileNameRegex = std::regex{ R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))" };
const std::regex EraseBufferInfo::fileNameRegex = std::regex{ R"([1-5]_E_([0-9]*)_([0-9]+))" };

void WriteBufferInfo::updateInternalBufferInfos(vector<InternalBufferInfo>& internalBufferInfos) {
	internalBufferInfos[lba].cmd = CMD_WRITE;
	internalBufferInfos[lba].data = written_data;
}

void EraseBufferInfo::updateInternalBufferInfos(vector<InternalBufferInfo>& internalBufferInfos) {
	for (int count = 0; count < size; count++) {
		internalBufferInfos[lba + count].cmd = CMD_ERASE;
		internalBufferInfos[lba + count].data = NAND_DATA_EMPTY;
	}
}

void EmptyBufferInfo::updateInternalBufferInfos(vector<InternalBufferInfo>& internalBufferInfos) {
	// emptyBufferInfo는 InternalBufferInfo 에 아무런 영향을 주지 않습니다.
}

string WriteBufferInfo::getFileName(int bufIndex) {
	std::ostringstream oss;
	oss << bufIndex + 1 << "_W_" << lba << "_" << written_data;
	string fileName = oss.str();
	return fileName;
}

string EraseBufferInfo::getFileName(int bufIndex) {
	std::ostringstream oss;
	oss << bufIndex + 1 << "_E_" << lba << "_" << size;
	string fileName = oss.str();
	return fileName;
}

string EmptyBufferInfo::getFileName(int bufIndex) {
	std::ostringstream oss;
	oss << bufIndex + 1 << "_empty";
	string fileName = oss.str();
	return fileName;
}

