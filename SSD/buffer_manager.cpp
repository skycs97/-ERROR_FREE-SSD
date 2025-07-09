#include "buffer_manager.h"
#include <regex>
#include <string>
#include <sstream>
#include <iomanip>

void BufferManager::init() {
	fileHandler->createDirIfNotExist(BUFFER_DIR_NAME);

	for (int buffer_num = 1; buffer_num <= BUFFER_SIZE; buffer_num++)
	{
		if (existBufferFile(buffer_num))
		{
			updateBufferState(buffer_num);
		}
		else
		{
			createBufferFile(buffer_num);
		}
	}
}

bool BufferManager::existBufferFile(int buffer_num)
{
	string dir_path = BUFFER_DIR_NAME "\\*";
	string file_name = getBufferFilePreFix(buffer_num);
	if (fileHandler->isExist(dir_path, file_name)) return true;
	return false;
}

void BufferManager::createBufferFile(int buffer_num)
{
	string file_path = BUFFER_DIR_NAME "\\";
	file_path += string(getBufferFilePreFix(buffer_num)) + BUFFER_NAME_EMPTY;
	fileHandler->createEmptyFile(file_path);
	return;
}

const char* BufferManager::getBufferFilePreFix(int buffer_num)
{
	switch (buffer_num) {
	case 1: return PREFIX_BUFFER_FILE1;
	case 2: return PREFIX_BUFFER_FILE2;
	case 3: return PREFIX_BUFFER_FILE3;
	case 4: return PREFIX_BUFFER_FILE4;
	case 5: return PREFIX_BUFFER_FILE5;
	default: return "";
	}
}

void BufferManager::updateBufferState(int buffer_num)
{
	// TODO
}

bool BufferManager::isBufferFull() {
	return getUsedBufferCount() == BUFFER_SIZE;
}

bool BufferManager::read(int lba, string& outputData) {
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

int BufferManager::getUsedBufferCount() {
	return buffers.size();
}