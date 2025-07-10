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
	string empty_file_name = getBufferFilePrefix(buf_idx) + BUFFER_NAME_EMPTY;
	if (fileHandler->isExist(dir_path, empty_file_name)) return false;

	string file_name = getBufferFilePrefix(buf_idx);
	if (fileHandler->isExist(dir_path, file_name, 2)) return true;
	return false;
}

void BufferManager::createBufferFile(int buf_idx)
{
	string file_name = getBufferFilePrefix(buf_idx) + BUFFER_NAME_EMPTY;
	string file_path = BUFFER_DIR_NAME "\\";
	file_path += file_name;
	fileHandler->createEmptyFile(file_path);
	fillBufferInfo(file_name, buf_idx);
}

string BufferManager::getBufferFilePrefix(int buf_idx)
{
	return std::to_string(buf_idx+1) + "_";
}

void BufferManager::updateBufferState(int buf_idx)
{
	vector<string> buffer_fname = fileHandler->findFileUsingPrefix(BUFFER_DIR_NAME, getBufferFilePrefix(buf_idx));

	if (buffer_fname.size() > 1) throw std::exception("There are many buffer files in same prefix.");

	fillBufferInfo(buffer_fname.front(), buf_idx);
	IncreaseBufferCnt();

	updateInternalBufferState();
}

void BufferManager::updateInternalBufferState()
{
	for (int buf_idx = 0; buf_idx < BUFFER_SIZE; buf_idx++) {
		if (buffers[buf_idx].cmd == CMD_WRITE) {
			fillInternalBufferWrite(buf_idx);
		}
		else if (buffers[buf_idx].cmd == CMD_ERASE) {
			fillInternalBufferErase(buf_idx);
		}

		if (buffers[buf_idx].cmd == INVALID_VALUE) break;
	}
}

void BufferManager::fillInternalBufferErase(int buf_idx)
{
	int lba = buffers[buf_idx].lba;
	int size = buffers[buf_idx].erase_size;
	for (int count = 0; count < size; count++) {
		internalBuffers[lba + count].cmd = CMD_ERASE;
		internalBuffers[lba + count].data = NAND_DATA_EMPTY;
	}
}

void BufferManager::fillInternalBufferWrite(int buf_idx)
{
	int lba = buffers[buf_idx].lba;
	const string& data = buffers[buf_idx].written_data;
	internalBuffers[lba].cmd = CMD_WRITE;
	internalBuffers[lba].data = data;
}

CMD_TYPE BufferManager::getBufferTypeFromFilenames(const string& fname) {
	std::regex writeRegex(R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))");
	std::regex eraseRegex(R"([1-5]_E_([0-9]*)_([0-9]+))");

	if (std::regex_match(fname, writeRegex)) {
		return CMD_WRITE;
	}
	else if (std::regex_match(fname, eraseRegex)) {
		return CMD_ERASE;
	}
	return INVALID_VALUE;
}

void BufferManager::fillBufferInfo(string fname, int buf_idx)
{
	if (buf_idx < 0 || buf_idx >= BUFFER_SIZE) throw std::exception("invalid buffer index.");

	CMD_TYPE bufferType = getBufferTypeFromFilenames(fname);
	if (bufferType == CMD_WRITE) {
		setWriteBufferInfo(buf_idx, fname);
		return;
	}
	if (bufferType == CMD_ERASE) {
		setEraseBufferInfo(buf_idx, fname);
		return;
	}
	setEmptyBufferInfo(buf_idx, fname);
	return;
}

void BufferManager::setEmptyBufferInfo(int buf_idx, const string& fname)
{
	setBufferInfo(buf_idx,
		INVALID_VALUE,
		INVALID_VALUE,
		"",
		INVALID_VALUE);
}

void BufferManager::setEraseBufferInfo(int buf_idx, const string& fname)
{
	std::regex writeRegex(R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))");
	std::smatch m;
	std::regex_search(fname, m, writeRegex);
	setBufferInfo(buf_idx,
		CMD_ERASE,
		std::atoi(m.str(1).c_str())/*LBA*/,
		""/*data*/,
		std::atoi(m.str(2).c_str())/*erase size*/);
}

void BufferManager::setWriteBufferInfo(int buf_idx, const string& fname)
{
	std::regex writeRegex(R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))");
	std::smatch m;
	std::regex_search(fname, m, writeRegex);
	setBufferInfo(buf_idx,
		CMD_WRITE,
		std::atoi(m.str(1).c_str())/*LBA*/,
		m.str(2)/*data*/,
		INVALID_VALUE/*erase size*/);
}

void BufferManager::setBufferInfo(int buf_idx,
	CMD_TYPE cmd,
	int lba,
	string written_data,
	int size)
{
	if (buf_idx < 0 || buf_idx >= BUFFER_SIZE) throw std::exception("invalid buffer_num.");
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

	int buf_idx = 0;
	for (int internalBufferIdx = 0; internalBufferIdx < 100; internalBufferIdx++) {
		InternalBufferInfo& internalBuffer = internalBuffers[internalBufferIdx];
		if (meetErase == false) {
			if (internalBuffer.cmd == CMD_ERASE) {
				meetErase = true;
				eraseStartLBA = internalBufferIdx;
				write_lbas.clear();
			}
			else if (internalBuffer.cmd == CMD_WRITE) {
				fillWriteBufferInfo(internalBufferIdx, buf_idx);
				buf_idx++;
			}
		}
		else {
			if (internalBuffer.cmd == CMD_WRITE) {
				// erase 사이에 등장한 write는 따로 기록해 둡니다.
				write_lbas.push_back(internalBufferIdx);
			}
			else if (internalBuffer.cmd == INVALID_VALUE) {
				// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.
				int erase_count = internalBufferIdx - eraseStartLBA;
				fillEraseBufferInfo(buf_idx, eraseStartLBA, erase_count);
				buf_idx++;
				for (int write_lba : write_lbas) {
					fillWriteBufferInfo(write_lba, buf_idx);
					buf_idx++;
				}
				meetErase = false;
			}

			else if (internalBufferIdx == 99 || internalBufferIdx - eraseStartLBA == 9) {
				// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.
				int erase_count = internalBufferIdx - eraseStartLBA + 1;
				fillEraseBufferInfo(buf_idx, eraseStartLBA, erase_count);
				buf_idx++;
				for (int write_lba : write_lbas) {
					fillWriteBufferInfo(write_lba, buf_idx);
					buf_idx++;
				}
				meetErase = false;
			}
		}
	}
	valid_buf_cnt = buf_idx;
	for (; buf_idx < BUFFER_SIZE; buf_idx++) {
		// empty Buffer도 기록합니다.
		fillEmptyBufferInfo(buf_idx);
	}
}

string BufferInfo::getFileName(int buf_idx) {
	std::ostringstream oss;
	if (cmd == INVALID_VALUE) {
		oss << buf_idx + 1 << "_empty";
	}
	else if (cmd == CMD_WRITE) {
		oss << buf_idx + 1 << "_W_" << lba << "_" << written_data;
	}
	else if (cmd == CMD_ERASE) {
		oss << buf_idx + 1 << "_E_" << lba << "_" << erase_size;
	}
	return oss.str();
}

void BufferManager::fillEmptyBufferInfo(int buf_idx)
{
	string old_name = buffers[buf_idx].getFileName(buf_idx);
	setBufferInfo(buf_idx, INVALID_VALUE, INVALID_VALUE, "", INVALID_VALUE);
	string new_name = buffers[buf_idx].getFileName(buf_idx);
	writeBuffer(old_name, new_name);
}
void BufferManager::fillWriteBufferInfo(int write_lba, int buf_idx)
{
	string old_name = buffers[buf_idx].getFileName(buf_idx);
	string data = internalBuffers[write_lba].data;
	setBufferInfo(buf_idx, CMD_WRITE, write_lba, data, INVALID_VALUE);
	string new_name = buffers[buf_idx].getFileName(buf_idx);
	writeBuffer(old_name, new_name);
}
void BufferManager::fillEraseBufferInfo(int buf_idx, int erase_start, int erase_count)
{
	string old_name = buffers[buf_idx].getFileName(buf_idx);
	setBufferInfo(buf_idx, CMD_ERASE, erase_start, "", erase_count);
	string new_name = buffers[buf_idx].getFileName(buf_idx);
	writeBuffer(old_name, new_name);
}
void BufferManager::addWriteCommand(int lba, const string& data) {
	if (data == NAND_DATA_EMPTY) {
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
		internalBuffers[i] = { CMD_ERASE, NAND_DATA_EMPTY };
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
		fillEmptyBufferInfo(buf_idx);
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
	if (old_name == new_name){
		return;
	}
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