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
	for (int buf_idx = getUsedBufferCount() - 1; buf_idx >= 0; buf_idx--) {
		if (buffers[buf_idx].cmd == CMD_ERASE)
		{
			int lba_start = buffers[buf_idx].lba;
			int lba_end = lba_start + buffers[buf_idx].erase_size - 1;
			if (lba_start <= lba && lba <= lba_end)
			{
				outputData = NAND_DATA_EMPTY;
				return true;
			}
		}
		else if (buffers[buf_idx].cmd == CMD_WRITE)
		{
			if (lba == buffers[buf_idx].lba)
			{
				outputData = buffers[buf_idx].written_data;
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
	
	int new_buf_idx = getUsedBufferCount();
	std::ostringstream oss;
	oss << new_buf_idx + 1 << "_W_" << lba <<"_"<< data;
	fillBufferInfo(oss.str(), new_buf_idx, true);
	IncreaseBufferCnt();
}

void BufferManager::addEraseCommand(int lba, int count) {
	if (isBufferFull()) {
		flush();
	}
	//로직 구현
	int new_buf_idx = getUsedBufferCount();
	std::ostringstream oss;
	oss << new_buf_idx + 1 << "_E_" << lba <<"_"<<count;
	fillBufferInfo(oss.str(), new_buf_idx, true);
	IncreaseBufferCnt();
}

void BufferManager::flush() {
	vector<string> datas = nandFlashMemory->read();
	int buf_cnt = getUsedBufferCount();
	for (int buf_idx = 0; buf_idx < buf_cnt; buf_idx++) {
		if (buffers[buf_idx].cmd == CMD_WRITE)
		{
			datas[buffers[buf_idx].lba] = buffers[buf_idx].written_data;
		}
		else if (buffers[buf_idx].cmd == CMD_ERASE)
		{
			int lba_start = buffers[buf_idx].lba;
			int lba_end = lba_start + buffers[buf_idx].erase_size - 1;
			for (int lba = lba_start; lba <= lba_end; lba++)
			{
				datas[lba] = NAND_DATA_EMPTY;
			}
		}

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