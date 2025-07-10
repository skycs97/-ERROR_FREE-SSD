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


void BufferManager::init() {
	fileHandler->createDirectory(BUFFER_DIR_NAME);
	
	for (int bufIndex = 0; bufIndex < BUFFER_SIZE; bufIndex++)
	{
		if (existBufferFile(bufIndex)) updateBufferState(bufIndex);
		else createEmptyBufferFile(bufIndex);
	}
}

bool BufferManager::existBufferFile(int bufIndex)
{
	string dir_path = BUFFER_DIR_NAME "\\*";
	string empty_file_name = getBufferFilePrefix(bufIndex) + BUFFER_NAME_EMPTY;
	if (fileHandler->isFileExistByMatchLength(dir_path, empty_file_name, empty_file_name.length())) return false;

	string prefix_name = getBufferFilePrefix(bufIndex);
	if (fileHandler->isFileExistByMatchLength(dir_path, prefix_name, prefix_name.length())) return true;
	return false;
}

void BufferManager::createEmptyBufferFile(int bufIndex)
{
	string file_name = getBufferFilePrefix(bufIndex) + BUFFER_NAME_EMPTY;
	string file_path = BUFFER_DIR_NAME "\\";
	file_path += file_name;
	fileHandler->createFile(file_path);
	fillBufferInfo(file_name, bufIndex);
}

void BufferManager::updateBufferState(int bufIndex)
{
	vector<string> buffer_fname = fileHandler->findFileUsingPrefix(BUFFER_DIR_NAME, getBufferFilePrefix(bufIndex));

	if (buffer_fname.size() > 1) throw std::exception("There are many buffer files in same prefix.");

	fillBufferInfo(buffer_fname.front(), bufIndex);
	IncreaseBufferCnt();

	updateInternalBufferState();
}

string BufferManager::getBufferFilePrefix(int bufIndex)
{
	return std::to_string(bufIndex+1) + "_";
}

void BufferManager::updateInternalBufferState()
{
	for (int bufIndex = 0; bufIndex < BUFFER_SIZE; bufIndex++) {
		buffers[bufIndex]->updateInternalBufferInfos(internalBuffers);
	}
}

void BufferManager::fillBufferInfo(string fname, int bufIndex)
{
	if (bufIndex < 0 || bufIndex >= BUFFER_SIZE) throw std::exception("invalid buffer index.");

	CMD_TYPE bufferType = getBufferTypeFromFilenames(fname);
	if (bufferType == CMD_WRITE) {
		buffers[bufIndex] = new WriteBufferInfo(fname);
		return;
	}
	if (bufferType == CMD_ERASE) {
		buffers[bufIndex] = new EraseBufferInfo(fname);
		return;
	}
	if (bufferType == BUFFER_EMPTY) {
		buffers[bufIndex] = new EmptyBufferInfo();
		return;
	}
}

CMD_TYPE BufferManager::getBufferTypeFromFilenames(const string& fname) {
	if (std::regex_match(fname, WriteBufferInfo::fileNameRegex)) {
		return CMD_WRITE;
	}
	else if (std::regex_match(fname, EraseBufferInfo::fileNameRegex)) {
		return CMD_ERASE;
	}
	return BUFFER_EMPTY;
}

bool BufferManager::isBufferFull() {
	return getUsedBufferCount() == BUFFER_SIZE;
}

bool BufferManager::read(int lba, string& outputData) {
	if (internalBuffers[lba].cmd == BUFFER_EMPTY) return false;
	outputData = internalBuffers[lba].data;
	return true;
}

void BufferManager::addWriteCommand(int lba, const string& data) {
	if (data == NAND_DATA_EMPTY) {
		addEraseCommand(lba, 1);
		return;
	}
	if (isBufferFull()) {
		flush();
	}
	setInternalBufferWrite(lba, data);
	WriteUpdatedBufferFiles();
}


void BufferManager::addEraseCommand(int lba, int count) {
	if (isBufferFull()) {
		flush();
	}
	SetInternalBufferErase(lba, count);
	WriteUpdatedBufferFiles();
}

void BufferManager::flush() {
	vector<string> datas = nandFlashMemory->read();
	updateNandData(datas);
	flushInternalBuffers();
	writeEmptyBufferFiles();

	nandFlashMemory->write(datas);
}

void BufferManager::setInternalBufferWrite(int lba, const std::string& data)
{
	internalBuffers[lba] = { CMD_WRITE, data };
}

void BufferManager::SetInternalBufferErase(int lba, int count)
{
	for (int i = lba; i < lba + count; i++) {
		internalBuffers[i] = { CMD_ERASE, NAND_DATA_EMPTY };
	}
}

void BufferManager::WriteUpdatedBufferFiles()
{
	vector<string> oldNames = getOldFileNames();
	updateBufferByInternalBuffer();
	writeAllBufferFiles(oldNames);
}

void BufferManager::writeEmptyBufferFiles()
{
	vector<string> oldNames = getOldFileNames();
	valid_buf_cnt = 0;
	fillEmptyBuffers();
	writeAllBufferFiles(oldNames);
}

void BufferManager::updateBufferByInternalBuffer() {
	int eraseStartLBA = -1;
	bool meetErase = false;
	vector<int> writeLBAs;
	vector<string> old_names = getOldFileNames();
	int buf_idx = MIN_LBA;
	for (int internalBufferIdx = MIN_LBA; internalBufferIdx <= MAX_LBA; internalBufferIdx++) {
		InternalBufferInfo& internalBuffer = internalBuffers[internalBufferIdx];
		if (meetErase == false) {
			if (internalBuffer.cmd == CMD_ERASE) {
				meetErase = true;
				eraseStartLBA = internalBufferIdx;
				writeLBAs.clear();

				if(isLastLBA(internalBufferIdx))
					fillEraseBufferInfo(buf_idx, eraseStartLBA, 1);
			}
			else if (internalBuffer.cmd == CMD_WRITE) {
				bufIndex = createWriteBuffer(internalBuffer.data, bufIndex, internalBufferIdx);
			}
		}
		else {
			if (internalBuffer.cmd == CMD_WRITE) {
				writeLBAs.push_back(internalBufferIdx);
			}

			if (meetErase == true && (internalBufferIdx == MAX_LBA || internalBufferIdx - eraseStartLBA + 1 == MAX_ERASE_COUNT)) {
				int eraseCount = internalBufferIdx - eraseStartLBA + 1;
				bufIndex = createEraseBufferAndPassedWriteBuffer(eraseStartLBA, eraseCount, bufIndex, writeLBAs);
				meetErase = false;
			}
			if (internalBuffer.cmd == BUFFER_EMPTY) {
				int eraseCount = internalBufferIdx - eraseStartLBA;
				bufIndex = createEraseBufferAndPassedWriteBuffer(eraseStartLBA, eraseCount, bufIndex, writeLBAs);
				meetErase = false;
			}
		}
	}
	valid_buf_cnt = bufIndex;
	fillEmptyBuffers();
}

int BufferManager::createWriteBuffer(const string& data, int bufIndex, int internalBufferIdx)
{
	buffers[bufIndex++] = new WriteBufferInfo(internalBufferIdx, data);
	return bufIndex;
}

int BufferManager::createEraseBufferAndPassedWriteBuffer(int eraseStartLBA, int eraseCount, int bufIndex, std::vector<int>& writeLBAs)
{
	// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.	
	buffers[bufIndex++] = new EraseBufferInfo(eraseStartLBA, eraseCount);
	for (int writeLBA : writeLBAs) {
		string data = internalBuffers[writeLBA].data;
		buffers[bufIndex++] = new WriteBufferInfo(writeLBA, data);
	}
	return bufIndex;
}

vector<string> BufferManager::getOldFileNames()
{
	vector<string> oldNames;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		oldNames.push_back(buffers[i]->getFileName(i));
	}
	return oldNames;
}

void BufferManager::fillEmptyBuffers()
{
	for (int bufIndex = getUsedBufferCount(); bufIndex < BUFFER_SIZE; bufIndex++) {
		buffers[bufIndex] = new EmptyBufferInfo();
	}
}

void BufferManager::writeAllBufferFiles(std::vector<std::string>& oldNames)
{
	for (int i = 0; i < BUFFER_SIZE; i++) {
		const string& new_name = buffers[i]->getFileName(i);
		const string& old_name = oldNames[i];
		writeBufferFile(old_name, new_name);
	}
}

void BufferManager::updateNandData(std::vector<std::string>& outData)
{
	for (int index = 0; index <= MAX_LBA; index++) {
		if (internalBuffers[index].cmd == BUFFER_EMPTY) continue;
		outData[index] = internalBuffers[index].data;
	}
}

void BufferManager::flushInternalBuffers()
{
	for (int index = 0; index <= MAX_LBA; index++) {
		internalBuffers[index].cmd = BUFFER_EMPTY;
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