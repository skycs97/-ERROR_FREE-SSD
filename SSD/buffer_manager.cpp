#include "buffer_manager.h"
#include <regex>
#include <string>
#include <sstream>
#include <iomanip>

bool BufferManager::isBufferFull() {
	return getUsedBufferCount() == 5;
}

bool BufferManager::read(int lba, string& outputData) {
	readBuffer();
	for (int index = getUsedBufferCount() - 1; index >= 0; index--) {
		string data = buffers.at(index);
		std::smatch m;

		std::regex writeRegex(R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))");
		if (std::regex_search(data, m, writeRegex)) {
			int bufferLba = std::atoi(m.str(1).c_str());
			if (bufferLba == lba) {
				outputData = m.str(2);
				return true;
			}
		}
		std::regex eraseRegex(R"([1-5]_E_([0-9]*)_([0-9]+))");
		if (std::regex_search(data, m, eraseRegex)) {
			int lbaStart = std::atoi(m.str(1).c_str());
			int count = std::atoi(m.str(2).c_str());
			int lbaEnd = lbaStart + count;
			if (lba >= lbaStart && lba < lbaEnd) {
				outputData = "0x00000000";
				return true;
			}
		}
	}
	return false;
}

void BufferManager::addWriteCommand(int lba, const string& data) {
	readBuffer();
	if (isBufferFull()) {
		flush();
	}
	int index = getUsedBufferCount();

	std::ostringstream oss;
	oss << index + 1 << "_W_" << lba <<"_"<< data;
	buffers.push_back(oss.str());
	
	writeBuffer();
}

void BufferManager::addEraseCommand(int lba, int count) {
	readBuffer();
	if (isBufferFull()) {
		flush();
	}
	//로직 구현
	int index = getUsedBufferCount();

	std::ostringstream oss;
	oss << index + 1 << "_E_" << lba <<"_"<<count;
	buffers.push_back(oss.str());

	writeBuffer();
}

void BufferManager::flush() {
	vector<string> datas = nandFlashMemory->read();
	for (int index = 0; index < getUsedBufferCount(); index++) {
		string buffer = buffers.at(index);
		std::smatch m;

		std::regex writeRegex(R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))");
		if (std::regex_search(buffer, m, writeRegex)) {
			int lba = std::atoi(m.str(1).c_str());
			string data = m.str(2);
			datas[lba] = data;
			continue;
		}
		std::regex eraseRegex(R"([1-5]_E_([0-9]*)_([0-9]+))");
		if (std::regex_search(buffer, m, eraseRegex)) {
			int lbaStart = std::atoi(m.str(1).c_str());
			int count = std::atoi(m.str(2).c_str());
			int lbaEnd = lbaStart + count;

			for (int lba = lbaStart; lba < lbaEnd; lba++) {
				datas[lba] = "0x00000000";
			}
			continue;
		}
	}
	buffers.clear();
	nandFlashMemory->write(datas);
}

void BufferManager::writeBuffer() {
	//bufferData의 string을 이름으로 하는 file들 생성
}

void BufferManager::readBuffer() {
	//file을 읽어서 bufferData를 초기화
}

int BufferManager::getUsedBufferCount() {
	return buffers.size();
}