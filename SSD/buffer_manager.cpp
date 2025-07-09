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
	string file_name = getBufferFilePrefix(buffer_num);
	if (fileHandler->isExist(dir_path, file_name)) return true;
	return false;
}

void BufferManager::createBufferFile(int buffer_num)
{
	string file_name = string(getBufferFilePrefix(buffer_num)) + BUFFER_NAME_EMPTY;
	string file_path = BUFFER_DIR_NAME "\\";
	file_path += file_name;
	fileHandler->createEmptyFile(file_path);
	fillBufferInfo(file_name, buffer_num, false);
	return;
}

const char* BufferManager::getBufferFilePrefix(int buffer_num)
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
	vector<string> buffer_fname = fileHandler->findFileUsingPrefix(BUFFER_DIR_NAME, getBufferFilePrefix(buffer_num));
	
	if (buffer_fname.size() > 1) throw std::exception("There are many buffer files in same prefix.");
	
	fillBufferInfo(buffer_fname.front(), buffer_num, false);
	IncreaseBufferCnt();
}

void BufferManager::fillBufferInfo(string fname, int buffer_num, bool need_file_change)
{
	std::smatch m;
	std::regex writeRegex(R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))");
	std::regex eraseRegex(R"([1-5]_E_([0-9]*)_([0-9]+))");

	if (std::regex_search(fname, m, writeRegex)) {
		setBufferInfo(buffer_num,
			fname,
			CMD_WRITE,
			std::atoi(m.str(1).c_str())/*LBA*/,
			m.str(2)/*data*/,
			INVALID_VALUE/*erase size*/);
	}
	else if (std::regex_search(fname, m, eraseRegex)) {
		buffers[buffer_num].cmd = CMD_ERASE;
		buffers[buffer_num].erase_size = std::atoi(m.str(2).c_str());
		buffers[buffer_num].fname = fname;
		buffers[buffer_num].lba = std::atoi(m.str(1).c_str());
		buffers[buffer_num].written_data = INVALID_VALUE;
		setBufferInfo(buffer_num,
			fname,
			CMD_ERASE,
			std::atoi(m.str(1).c_str())/*LBA*/,
			""/*data*/,
			std::atoi(m.str(2).c_str())/*erase size*/);
	}
	else {
		setBufferInfo(buffer_num,
			"",
			INVALID_VALUE,
			INVALID_VALUE,
			"",
			INVALID_VALUE);
	}

	if (need_file_change)
	{
		writeBuffer(fname, buffer_num);
	}
}

void BufferManager::setBufferInfo(int buffer_num,
	string fname,
	CMD_TYPE cmd,
	int lba,
	string written_data,
	int size)
{
	buffers[buffer_num].fname = fname;
	buffers[buffer_num].cmd = cmd;
	buffers[buffer_num].lba = lba;
	buffers[buffer_num].written_data = written_data;
	buffers[buffer_num].erase_size = size;
}

bool BufferManager::isBufferFull() {
	return getUsedBufferCount() == BUFFER_SIZE;
}

bool BufferManager::read(int lba, string& outputData) {
	for (int index = getUsedBufferCount() - 1; index >= 0; index--) {
		if (buffers[index].cmd == CMD_ERASE)
		{
			int lba_start = buffers[index].lba;
			int lba_end = lba_start + buffers[index].erase_size - 1;
			if (lba_start <= lba && lba <= lba_end)
			{
				outputData = NAND_DATA_EMPTY;
				return true;
			}
		}
		else if (buffers[index].cmd == CMD_WRITE)
		{
			if (lba == buffers[index].lba)
			{
				outputData = buffers[index].written_data;
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
	fillBufferInfo(oss.str(), index, true);
	IncreaseBufferCnt();
}

void BufferManager::addEraseCommand(int lba, int count) {
	if (isBufferFull()) {
		flush();
	}
	//로직 구현
	int index = getUsedBufferCount();
	std::ostringstream oss;
	oss << index + 1 << "_E_" << lba <<"_"<<count;
	fillBufferInfo(oss.str(), index, true);
	IncreaseBufferCnt();
}

void BufferManager::flush() {
	vector<string> datas = nandFlashMemory->read();
	for (int index = 0; index < getUsedBufferCount(); index++) {
		if (buffers[index].cmd == CMD_WRITE)
		{
			datas[buffers[index].lba] = buffers[index].written_data;
		}
		else if (buffers[index].cmd == CMD_ERASE)
		{
			int lba_start = buffers[index].lba;
			int lba_end = lba_start + buffers[index].erase_size - 1;
			for (int lba = lba_start; lba <= lba_end; lba++)
			{
				datas[lba] = NAND_DATA_EMPTY;
			}
		}

		string file_name = string(getBufferFilePrefix(index)) + BUFFER_NAME_EMPTY;
		fillBufferInfo(file_name, index, true);
		DecreaseBufferCnt();
	}
	nandFlashMemory->write(datas);
}

void BufferManager::writeBuffer(const string& new_name, int buffer_num) {
	vector<string> old_name = fileHandler->findFileUsingPrefix(BUFFER_DIR_NAME, getBufferFilePrefix(buffer_num));
	if (old_name.size() > 1) throw std::exception("There are many buffer files in same prefix.");

	fileHandler->rename(old_name.front(), new_name);
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