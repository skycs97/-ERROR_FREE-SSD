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

	updateInternalBufferState();
}

void BufferManager::updateInternalBufferState()
{
	for (int buffer_idx = 0; buffer_idx < BUFFER_SIZE; buffer_idx++) {
		if (buffers[buffer_idx].cmd == INVALID_VALUE) continue;
		else if (buffers[buffer_idx].cmd == CMD_WRITE) {
			int lba = buffers[buffer_idx].lba;
			const string& data = buffers[buffer_idx].written_data;
			internalBuffers[lba].cmd = CMD_WRITE;
			internalBuffers[lba].data = data;
		}
		else if (buffers[buffer_idx].cmd == CMD_ERASE) {
			int lba = buffers[buffer_idx].lba;
			int size = buffers[buffer_idx].erase_size;
			for (int count = 0; count < size; count++) {
				internalBuffers[lba + count].cmd = CMD_ERASE;
				internalBuffers[lba + count].data = ERASED_VALUE;
			}
		}
	}
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
	int eraseStartLBA = -1;
	bool meetErase = false;
	vector<int> write_lbas;

	int buffer_idx = 0;
	for (int internalBufferIdx = 0; internalBufferIdx < 100; internalBufferIdx++) {
		InternalBufferInfo& internalBuffer = internalBuffers[internalBufferIdx];
		if (meetErase == false) {
			if (internalBuffer.cmd == CMD_ERASE) {
				meetErase = true;
				eraseStartLBA = internalBufferIdx;
				write_lbas.clear();
			}
			else if (internalBuffer.cmd == CMD_WRITE) {
				fillWriteBufferInfo(internalBufferIdx, buffer_idx);
				buffer_idx++;
			}
		}
		else {
			if (internalBuffer.cmd == CMD_WRITE) {
				// erase 사이에 등장한 write는 따로 기록해 둡니다.
				write_lbas.push_back(internalBufferIdx);
			}
			else if (internalBuffer.cmd == INVALID_VALUE) {
				// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.
				int erase_count = internalBufferIdx - eraseStartLBA - 1;
				fillEraseBufferInfo(buffer_idx, eraseStartLBA, erase_count);
				buffer_idx++;
				for (int write_lba : write_lbas) {
					fillWriteBufferInfo(write_lba, buffer_idx);
					buffer_idx++;
				}
				meetErase = false;
			}

			else if (internalBufferIdx == 99 || internalBufferIdx - eraseStartLBA == 10) {
				// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.
				int erase_count = internalBufferIdx - eraseStartLBA;
				fillEraseBufferInfo(buffer_idx, eraseStartLBA, erase_count);
				buffer_idx++;
				for (int write_lba : write_lbas) {
					fillWriteBufferInfo(write_lba, buffer_idx);
					buffer_idx++;
				}
				meetErase = false;
			}
		}
	}
	valid_buf_cnt = buffer_idx;
	for (; buffer_idx < BUFFER_SIZE; buffer_idx++) {
		// empty Buffer도 기록합니다.
		fillEmptyBufferInfo(buffer_idx);
	}
}
void BufferManager::fillEmptyBufferInfo(int buffer_idx)
{
	std::ostringstream oss;
	oss << buffer_idx + 1 << "_empty";
	fillBufferInfo(oss.str(), buffer_idx, true);
}
void BufferManager::fillWriteBufferInfo(int write_lba, int buffer_idx)
{
	string data = internalBuffers[write_lba].data;
	std::ostringstream oss;
	oss << buffer_idx + 1 << "_W_" << write_lba << "_" << data;
	fillBufferInfo(oss.str(), buffer_idx, true);
}
void BufferManager::fillEraseBufferInfo(int buffer_idx, int erase_start, int erase_count)
{
	std::ostringstream oss;
	oss << buffer_idx + 1 << "_E_" << erase_start << "_" << erase_count;
	fillBufferInfo(oss.str(), buffer_idx, true);
}
void BufferManager::addWriteCommand(int lba, const string& data) {
	if (data == ERASED_VALUE) {
		addEraseCommand(lba, 1);
		return;
	}
	if (isBufferFull()) {
		flush();
	}
	internalBuffers[lba] = { CMD_WRITE, data };
	updateBuffer();
}

void BufferManager::addEraseCommand(int lba, int count) {
	if (isBufferFull()) {
		flush();
	}
	for (int i = lba; i < lba + count; i++) {
		internalBuffers[i] = { CMD_ERASE, ERASED_VALUE };
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
	initInternalBuffers();

	// 외부 버퍼 초기화
	int buf_cnt = getUsedBufferCount();
	for (int buf_idx = 0; buf_idx < buf_cnt; buf_idx++) {
		string file_name = string(getBufferFilePrefix(buf_idx)) + BUFFER_NAME_EMPTY;
		fillBufferInfo(file_name, buf_idx, true);
	}
	nandFlashMemory->write(datas);
	valid_buf_cnt = 0;
}

void BufferManager::initInternalBuffers()
{
	for (int index = 0; index < 100; index++) {
		internalBuffers[index].cmd = INVALID_VALUE;
		internalBuffers[index].data = "";
	}
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