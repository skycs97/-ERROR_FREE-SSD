#include "buffer_manager.h"
#include <regex>
#include <string>
#include <sstream>
#include <iomanip>

void BufferManager::init() {
	fileHandler->createDirIfNotExist(BUFFER_DIR_NAME);

	for (int buf_idx = 0; buf_idx < BUFFER_SIZE; buf_idx++)
	{
		if (existBufferFile(buf_idx)) updateBufferState(buf_idx);
		else createBufferFile(buf_idx);
	}
}

bool BufferManager::existBufferFile(int buf_idx)
{
	string dir_path = BUFFER_DIR_NAME "\\*";
	string empty_file_name = string(getBufferFilePrefix(buf_idx)) + BUFFER_NAME_EMPTY;
	if (fileHandler->isExist(dir_path, empty_file_name)) return false;

	string file_name = getBufferFilePrefix(buf_idx);
	if (fileHandler->isExist(dir_path, file_name, 2)) return true;
	return false;
}

void BufferManager::createBufferFile(int buf_idx)
{
	string file_name = string(getBufferFilePrefix(buf_idx)) + BUFFER_NAME_EMPTY;
	string file_path = BUFFER_DIR_NAME "\\";
	file_path += file_name;
	fileHandler->createEmptyFile(file_path);
	fillBufferInfo(file_name, buf_idx, false);
	return;
}

const char* BufferManager::getBufferFilePrefix(int buf_idx)
{
	switch (buf_idx) {
	case 0: return PREFIX_BUFFER_FILE1;
	case 1: return PREFIX_BUFFER_FILE2;
	case 2: return PREFIX_BUFFER_FILE3;
	case 3: return PREFIX_BUFFER_FILE4;
	case 4: return PREFIX_BUFFER_FILE5;
	default: return "";
	}
}

void BufferManager::updateBufferState(int buf_idx)
{
	vector<string> buffer_fname = fileHandler->findFileUsingPrefix(BUFFER_DIR_NAME, getBufferFilePrefix(buf_idx));
	
	if (buffer_fname.size() > 1) throw std::exception("There are many buffer files in same prefix.");
	
	fillBufferInfo(buffer_fname.front(), buf_idx, false);
	IncreaseBufferCnt();
}

void BufferManager::fillBufferInfo(string fname, int buf_idx, bool need_file_change)
{
	if (buf_idx < 0 || buf_idx >= BUFFER_SIZE) throw std::exception("invalid buffer index.");

	std::smatch m;
	std::regex writeRegex(R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))");
	std::regex eraseRegex(R"([1-5]_E_([0-9]*)_([0-9]+))");
	string old_name = buffers[buf_idx].fname;

	if (std::regex_search(fname, m, writeRegex)) {
		setBufferInfo(buf_idx,
			fname,
			CMD_WRITE,
			std::atoi(m.str(1).c_str())/*LBA*/,
			m.str(2)/*data*/,
			INVALID_VALUE/*erase size*/);
	}
	else if (std::regex_search(fname, m, eraseRegex)) {
		setBufferInfo(buf_idx,
			fname,
			CMD_ERASE,
			std::atoi(m.str(1).c_str())/*LBA*/,
			""/*data*/,
			std::atoi(m.str(2).c_str())/*erase size*/);
	}
	else {
		setBufferInfo(buf_idx,
			fname,
			INVALID_VALUE,
			INVALID_VALUE,
			"",
			INVALID_VALUE);
	}

	if (need_file_change)
	{
		writeBuffer(old_name, fname);
	}
}

void BufferManager::setBufferInfo(int buf_idx,
	string fname,
	CMD_TYPE cmd,
	int lba,
	string written_data,
	int size)
{
	if (buf_idx < 0 || buf_idx >= BUFFER_SIZE) throw std::exception("invalid buffer_num.");

	buffers[buf_idx].fname = fname;
	buffers[buf_idx].cmd = cmd;
	buffers[buf_idx].lba = lba;
	buffers[buf_idx].written_data = written_data;
	buffers[buf_idx].erase_size = size;
}

bool BufferManager::isBufferFull() {
	return getUsedBufferCount() == BUFFER_SIZE;
}

bool BufferManager::read(int lba, string& outputData) {
	if (internalBuffers[lba].cmd == INVALID_VALUE) return false;
	outputData = internalBuffers[lba].data;
	return true;
}
void BufferManager::updateBuffer() {
	int erase_start = -1;
	int erase_count = 0;
	bool erase_flag = false;
	vector<int> write_lbas;

	int buffer_idx = 0;
	for (int i = 0; i < 100; i++) {
		if (erase_flag == true) {
			if (internalBuffers[i].cmd == CMD_ERASE) {
				erase_count++;
			}
			else if (internalBuffers[i].cmd == CMD_WRITE) {
				erase_count++;
				write_lbas.push_back(i);
			}

			if (i == 99 || erase_count == 10 || internalBuffers[i].cmd == INVALID_VALUE) {
				std::ostringstream oss;
				oss << buffer_idx + 1 << "_E_" << erase_start << "_" << erase_count;
				setBufferInfo(buffer_idx, oss.str(), CMD_ERASE, erase_start, "", erase_count);
				buffer_idx++;
				for (int write_lba : write_lbas) {
					string data = internalBuffers[write_lba].data;
					std::ostringstream oss;
					oss << buffer_idx + 1 << "_W_" << write_lba << "_" << data;
					setBufferInfo(buffer_idx, oss.str(), CMD_WRITE, write_lba, data, INVALID_VALUE);
					buffer_idx++;
				}
				erase_flag = false;
				erase_count = 0;
				write_lbas.clear();
			}
		}
		else {
			if (internalBuffers[i].cmd == CMD_WRITE) {
				string data = internalBuffers[i].data;
				std::ostringstream oss;
				oss << buffer_idx + 1 << "_W_" << i << "_" << data;
				setBufferInfo(buffer_idx, "", CMD_WRITE, i, data, INVALID_VALUE);
				buffer_idx++;
			}
			else if (internalBuffers[i].cmd == CMD_ERASE) {
				erase_flag = true;
				erase_start = i;
				erase_count = 1;
				write_lbas.clear();
			}
		}
	}
	valid_buf_cnt = buffer_idx;

}
void BufferManager::addWriteCommand(int lba, const string& data) {
	if (isBufferFull()) {
		flush();
	}

	if (data == "0x00000000") {
		addEraseCommand(lba, 1);
		return;
	}
	internalBuffers[lba] = { CMD_WRITE, data };

	updateBuffer();
}

void BufferManager::addEraseCommand(int lba, int count) {
	if (isBufferFull()) {
		flush();
	}
	//로직 구현

	for (int i = lba; i < lba + count; i++) {
		internalBuffers[i] = { CMD_ERASE, "0x00000000" };
	}

	updateBuffer();
}

void BufferManager::flush() {
	vector<string> datas = nandFlashMemory->read();

	// nand 에 쓸 데이터 업데이트
	for (int index = 0; index < 100; index++) {
		if (internalBuffers[index].cmd == INVALID_VALUE) continue;
		datas[index] = internalBuffers[index].data;
	}

	// 내부 버퍼 초기화
	for (int index = 0; index < 100; index++) {
		internalBuffers[index].cmd = INVALID_VALUE;
		internalBuffers[index].data = "";
	}

	// 외부 버퍼 초기화
	int buf_cnt = getUsedBufferCount();
	for (int buf_idx = 0; buf_idx < buf_cnt; buf_idx++) {
		string file_name = string(getBufferFilePrefix(buf_idx)) + BUFFER_NAME_EMPTY;
		fillBufferInfo(file_name, buf_idx, true);
		DecreaseBufferCnt();
	}
	nandFlashMemory->write(datas);
}

void BufferManager::writeBuffer(const string& old_name, const string& new_name) {
	string old_path = BUFFER_DIR_NAME "\\";
	old_path += old_name;
	string new_path = BUFFER_DIR_NAME "\\";
	new_path += new_name;
	fileHandler->rename(old_path, new_path);
}

int BufferManager::getUsedBufferCount() {
	return valid_buf_cnt;
}

void BufferManager::IncreaseBufferCnt()
{
	valid_buf_cnt++;
	if (valid_buf_cnt > BUFFER_SIZE) throw std::exception("valid_buf_cnt is over than 5!");
}

void BufferManager::DecreaseBufferCnt()
{
	valid_buf_cnt--;
	if (valid_buf_cnt < 0) throw std::exception("valid_buf_cnt is lower than 0!");
}