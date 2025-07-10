#include "buffer_manager.h"
#include <regex>
#include <string>
#include <sstream>
#include <iomanip>

const std::regex WriteBufferInfo::fileNameRegex = std::regex{ R"([1-5]_W_([0-9]*)_(0x[0-9A-Fa-f]+))" };
const std::regex EraseBufferInfo::fileNameRegex = std::regex{ R"([1-5]_E_([0-9]*)_([0-9]+))" };

void WriteBufferInfo::updateInternalBufferInfos(vector<InternalBufferInfo> internalBufferInfos) {
	internalBufferInfos[lba].cmd = CMD_WRITE;
	internalBufferInfos[lba].data = written_data;
}

void EraseBufferInfo::updateInternalBufferInfos(vector<InternalBufferInfo> internalBufferInfos) {
	for (int count = 0; count < size; count++) {
		internalBufferInfos[lba+count].cmd = CMD_ERASE;
		internalBufferInfos[lba+count].data = NAND_DATA_EMPTY;
	}
}

void EmptyBufferInfo::updateInternalBufferInfos(vector<InternalBufferInfo> internalBufferInfos) {
	// emptyBufferInfo는 InternalBufferInfo 에 아무런 영향을 주지 않습니다.
}

string WriteBufferInfo::getFileName(int buf_idx) {
	std::ostringstream oss;
	oss << buf_idx + 1 << "_W_" << lba << "_" << written_data;
	string fileName = oss.str();
	return fileName;
}

string EraseBufferInfo::getFileName(int buf_idx) {
	std::ostringstream oss;
	oss << buf_idx + 1 << "_E_" << lba << "_" << size;
	string fileName = oss.str();
	return fileName;
}

string EmptyBufferInfo::getFileName(int buf_idx) {
	std::ostringstream oss;
	oss << buf_idx + 1 << "_empty";
	string fileName = oss.str();
	return fileName;
}


void BufferManager::init() {
	fileHandler->createDirectory(BUFFER_DIR_NAME);
	
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
	if (fileHandler->isFileExistByMatchLength(dir_path, empty_file_name, empty_file_name.length())) return false;

	string prefix_name = getBufferFilePrefix(buf_idx);
	if (fileHandler->isFileExistByMatchLength(dir_path, prefix_name, prefix_name.length())) return true;
	return false;
}

void BufferManager::createBufferFile(int buf_idx)
{
	string file_name = getBufferFilePrefix(buf_idx) + BUFFER_NAME_EMPTY;
	string file_path = BUFFER_DIR_NAME "\\";
	file_path += file_name;
	fileHandler->createFile(file_path);
	fillBufferInfo(file_name, buf_idx);
}

string BufferManager::getBufferFilePrefix(int buf_idx)
{
	return std::to_string(buf_idx+1) + "_";
}

void BufferManager::updateBufferState(int buf_idx)
{
	vector<string> buffer_fname = fileHandler->getFileUsingPrefix(BUFFER_DIR_NAME, getBufferFilePrefix(buf_idx));

	if (buffer_fname.size() > 1) throw std::exception("There are many buffer files in same prefix.");

	fillBufferInfo(buffer_fname.front(), buf_idx);
	IncreaseBufferCnt();

	updateInternalBufferState();
}

void BufferManager::updateInternalBufferState()
{
	for (int buf_idx = 0; buf_idx < BUFFER_SIZE; buf_idx++) {
		buffers[buf_idx]->updateInternalBufferInfos(internalBuffers);
	}
}

CMD_TYPE BufferManager::getBufferTypeFromFilenames(const string& fname) {
	if (std::regex_match(fname, WriteBufferInfo::fileNameRegex)) {
		return CMD_WRITE;
	}
	else if (std::regex_match(fname, EraseBufferInfo::fileNameRegex)) {
		return CMD_ERASE;
	}
	return INVALID_VALUE;
}

void BufferManager::fillBufferInfo(string fname, int buf_idx)
{
	if (buf_idx < 0 || buf_idx >= BUFFER_SIZE) throw std::exception("invalid buffer index.");

	CMD_TYPE bufferType = getBufferTypeFromFilenames(fname);
	if (bufferType == CMD_WRITE) {
		buffers[buf_idx] = new WriteBufferInfo(fname);
		return;
	}
	if (bufferType == CMD_ERASE) {
		buffers[buf_idx] = new EraseBufferInfo(fname);
		return;
	}
	if (bufferType == INVALID_VALUE) {
		buffers[buf_idx] = new EmptyBufferInfo();
		return;
	}
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
	vector<string> old_names = getOldFileNames();
	int buf_idx = MIN_LBA;
	for (int internalBufferIdx = MIN_LBA; internalBufferIdx <= MAX_LBA; internalBufferIdx++) {
		InternalBufferInfo& internalBuffer = internalBuffers[internalBufferIdx];
		if (meetErase == false) {
			if (internalBuffer.cmd == CMD_ERASE) {
				meetErase = true;
				eraseStartLBA = internalBufferIdx;
				write_lbas.clear();

				if(isLastLBA(internalBufferIdx))
					fillEraseBufferInfo(buf_idx, eraseStartLBA, 1);
			}
			else if (internalBuffer.cmd == CMD_WRITE) {
				string data = internalBuffer.data;
				buffers[buf_idx] = new WriteBufferInfo(internalBufferIdx, data);
				buf_idx++;
			}
		}
		else {
			if (internalBuffer.cmd == CMD_WRITE) {
				// erase 사이에 등장한 write는 따로 기록해 둡니다.
				write_lbas.push_back(internalBufferIdx);
			}

			if (internalBuffer.cmd == INVALID_VALUE) {
				// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.
				int erase_count = internalBufferIdx - eraseStartLBA;
				buffers[buf_idx] = new EraseBufferInfo(eraseStartLBA, erase_count);
				buf_idx++;
				for (int write_lba : write_lbas) {
					string data = internalBuffers[write_lba].data;
					buffers[buf_idx] = new WriteBufferInfo(write_lba, data);
					buf_idx++;
				}
				meetErase = false;
			}
			
			if (meetErase == true && (internalBufferIdx == MAX_LBA || internalBufferIdx - eraseStartLBA == 9)) {
				// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.
				int erase_count = internalBufferIdx - eraseStartLBA + 1;
				buffers[buf_idx] = new EraseBufferInfo(eraseStartLBA, erase_count);
				buf_idx++;
				for (int write_lba : write_lbas) {
					string data = internalBuffers[write_lba].data;
					buffers[buf_idx] = new WriteBufferInfo(write_lba, data);
					buf_idx++;
				}
				meetErase = false;
			}
		}
	}
	
	valid_buf_cnt = buf_idx;
	fillEmptyBuffers();
	writeAllBufferFiles(old_names);
}

vector<string> BufferManager::getOldFileNames()
{
	vector<string> old_names;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		old_names.push_back(buffers[i]->getFileName(i));
	}
	return old_names;
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
	updateNandData(datas);
	initInternalBuffers();

	vector<string> old_names = getOldFileNames();
	valid_buf_cnt = 0;
	fillEmptyBuffers();
	writeAllBufferFiles(old_names);

	nandFlashMemory->write(datas);
}

void BufferManager::fillEmptyBuffers()
{
	for (int buf_idx = getUsedBufferCount(); buf_idx < BUFFER_SIZE; buf_idx++) {
		buffers[buf_idx] = new EmptyBufferInfo();
	}
}

void BufferManager::writeAllBufferFiles(std::vector<std::string>& old_names)
{
	for (int i = 0; i < BUFFER_SIZE; i++) {
		const string& new_name = buffers[i]->getFileName(i);
		const string& old_name = old_names[i];
		writeBufferFile(old_name, new_name);
	}
}

void BufferManager::updateNandData(std::vector<std::string>& outData)
{
	for (int index = 0; index < 100; index++) {
		if (internalBuffers[index].cmd == INVALID_VALUE) continue;
		outData[index] = internalBuffers[index].data;
	}
}

void BufferManager::initInternalBuffers()
{
	for (int index = 0; index <= MAX_LBA; index++) {
		internalBuffers[index].cmd = INVALID_VALUE;
		internalBuffers[index].data = "";
	}
}

void BufferManager::writeBufferFile(const string& old_name, const string& new_name) {
	if (old_name == new_name){
		return;
	}
	string old_path = BUFFER_DIR_NAME "\\" + old_name;
	string new_path = BUFFER_DIR_NAME "\\" + new_name;
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