#include "buffer_manager.h"

bool BufferManager::isBufferFull() {
	return false;
}

bool BufferManager::read(int lba, string& outputData) {
	return false;
}

void BufferManager::addWriteCommand(int lba, const string& data) {
	if (isBufferFull()) {
		flush();
	}

	//로직 구현

	updateBuffer();
}

void BufferManager::addEraseCommand(int lba, int count) {
	if (isBufferFull()) {
		flush();
	}
	//로직 구현

	updateBuffer();
}

void BufferManager::flush() {

}

void BufferManager::updateBuffer() {

}