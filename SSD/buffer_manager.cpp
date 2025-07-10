#include "buffer_manager.h"
#include "buffer_info.h"
#include "buffer_info_factory.h"
#include <regex>
#include <string>
#include <sstream>
#include <iomanip>

void BufferManager::init() {
	fileHandler->createDirectory(BUFFER_DIR_NAME);

	for (int bufIndex = 0; bufIndex < BUFFER_SIZE; bufIndex++)
	{
		if (existEmptyBufferFile(bufIndex)) {
			updateBufferState(bufIndex);
		}
		else if (existNonEmptyBufferFile(bufIndex)) {
			updateBufferState(bufIndex);
			IncreaseBufferCnt();
		}
		else createEmptyBufferFileAndUpdateState(bufIndex);
	}
	updateInternalBufferState();
}

bool BufferManager::existNonEmptyBufferFile(int bufIndex)
{
	string dirPath = BUFFER_DIR_NAME "\\*";
	string perfixName = getBufferFilePrefix(bufIndex);
	if (fileHandler->isFileExistByMatchLength(dirPath, perfixName, perfixName.length())) return true;
	return false;
}

bool BufferManager::existEmptyBufferFile(int bufIndex)
{
	string dirPath = BUFFER_DIR_NAME "\\*";
	string emptyFileName = getBufferFilePrefix(bufIndex) + BUFFER_NAME_EMPTY;
	if (fileHandler->isFileExistByMatchLength(dirPath, emptyFileName, emptyFileName.length())) return true;
	return false;
}

void BufferManager::createEmptyBufferFileAndUpdateState(int bufIndex)
{
	string fileName = getBufferFilePrefix(bufIndex) + BUFFER_NAME_EMPTY;

	fileHandler->createFile(BUFFER_DIR_NAME "\\" + fileName);

	fillBufferInfo(fileName, bufIndex);
}

void BufferManager::updateBufferState(int bufIndex)
{
	vector<string> bufferFileNames = fileHandler->getFileUsingPrefix(BUFFER_DIR_NAME, getBufferFilePrefix(bufIndex));

	if (bufferFileNames.size() > 1) throw std::exception("There are many buffer files in same prefix.");
	fillBufferInfo(bufferFileNames.front(), bufIndex);
}

string BufferManager::getBufferFilePrefix(int bufIndex)
{
	return std::to_string(bufIndex + 1) + "_";
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
	buffers[bufIndex] = BufferInfoFactory::getInstance().createCommand(fname);
}

void BufferManager::IncreaseBufferCnt()
{
	validBufCount++;
	if (validBufCount > BUFFER_SIZE) throw std::exception("validBufCount is over than 5!");
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
	updateBufferFiles();
}


void BufferManager::addEraseCommand(int lba, int count) {
	if (isBufferFull()) {
		flush();
	}
	SetInternalBufferErase(lba, count);
	updateBufferFiles();
}

bool BufferManager::isBufferFull() {
	return getUsedBufferCount() == BUFFER_SIZE;
}

void BufferManager::flush() {
	vector<string> datas = nandFlashMemory->read();
	updateNandData(datas);
	flushInternalBuffers();
	updateBufferFilesAllEmpty();

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

void BufferManager::updateBufferFiles()
{
	vector<string> oldNames = getOldFileNames();
	updateBufferByInternalBuffer();
	writeAllBufferFiles(oldNames);
}

void BufferManager::updateBufferFilesAllEmpty()
{
	vector<string> oldNames = getOldFileNames();
	validBufCount = 0;
	fillEmptyBuffers();
	writeAllBufferFiles(oldNames);
}

vector<string> BufferManager::getOldFileNames()
{
	vector<string> oldNames;
	for (int i = 0; i < BUFFER_SIZE; i++) {
		oldNames.push_back(getBufferFilePrefix(i) + buffers[i]->getFileName());
	}
	return oldNames;
}

void BufferManager::writeAllBufferFiles(std::vector<std::string>& oldNames)
{
	for (int i = 0; i < BUFFER_SIZE; i++) {
		const string& newName = getBufferFilePrefix(i) + buffers[i]->getFileName();
		const string& oldName = oldNames[i];
		writeBufferFile(oldName, newName);
	}
}

void BufferManager::writeBufferFile(const string& oldName, const string& newName) {
	if (oldName == newName) {
		return;
	}
	string old_path = BUFFER_DIR_NAME "\\" + oldName;
	string new_path = BUFFER_DIR_NAME "\\" + newName;
	fileHandler->rename(old_path, new_path);
}

void BufferManager::updateBufferByInternalBuffer() {
	int eraseStartLBA = -1;
	bool meetErase = false;
	vector<int> writeLBAs;
	int bufIndex = MIN_LBA;
	for (int internalBufferIdx = MIN_LBA; internalBufferIdx <= MAX_LBA; internalBufferIdx++) {
		InternalBufferInfo& internalBuffer = internalBuffers[internalBufferIdx];
		if (meetErase == false) {
			if (internalBuffer.cmd == CMD_ERASE) {
				meetErase = true;
				eraseStartLBA = internalBufferIdx;
				writeLBAs.clear();

				if (isLastLBA(internalBufferIdx)) {
					bufIndex = createEraseBufferAndPassedWriteBuffer(eraseStartLBA, 1, bufIndex, writeLBAs);
				}
			}
			else if (internalBuffer.cmd == CMD_WRITE) {
				bufIndex = createWriteBuffer(bufIndex, internalBufferIdx, internalBuffer.data);
			}
		}
		else {
			if (internalBuffer.cmd == CMD_WRITE) {
				writeLBAs.push_back(internalBufferIdx);
			}
			if (internalBuffer.cmd == BUFFER_EMPTY) {
				int eraseCount = internalBufferIdx - eraseStartLBA;
				bufIndex = createEraseBufferAndPassedWriteBuffer(eraseStartLBA, eraseCount, bufIndex, writeLBAs);
				meetErase = false;
			}
			if (meetErase == true && (internalBufferIdx == MAX_LBA || internalBufferIdx - eraseStartLBA + 1 == MAX_ERASE_COUNT)) {
				int eraseCount = internalBufferIdx - eraseStartLBA + 1;
				bufIndex = createEraseBufferAndPassedWriteBuffer(eraseStartLBA, eraseCount, bufIndex, writeLBAs);
				meetErase = false;
			}

		}
	}
	validBufCount = bufIndex;
	fillEmptyBuffers();
}

int BufferManager::createWriteBuffer(int bufIndex, int LBA, const string& data)
{
	buffers[bufIndex++] = BufferInfoFactory::getInstance().createWriteCommand(LBA, data);
	return bufIndex;
}

int BufferManager::createEraseBufferAndPassedWriteBuffer(int eraseStartLBA, int eraseCount, int bufIndex, std::vector<int>& writeLBAs)
{
	// erase 가 끝나면, eraseBuffer를 기록하고, 그 사이에 지나친 write 들도 기록합니다.	
	buffers[bufIndex++] = BufferInfoFactory::getInstance().createEraseCommand(eraseStartLBA, eraseCount);
	for (int writeLBA : writeLBAs) {
		string data = internalBuffers[writeLBA].data;
		bufIndex = createWriteBuffer(bufIndex, writeLBA, data);
	}
	return bufIndex;
}

void BufferManager::fillEmptyBuffers()
{
	for (int bufIndex = getUsedBufferCount(); bufIndex < BUFFER_SIZE; bufIndex++) {
		buffers[bufIndex] = new EmptyBufferInfo();
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

int BufferManager::getUsedBufferCount() {
	return validBufCount;
}