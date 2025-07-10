#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "nand_flash_memory_impl.h"

void NandFlashMemoryImpl::init()
{
	if (fileHandler->isFileExistByMatchLength(".", NAND_FILENAME, strlen(NAND_FILENAME))) return;

	if (fileHandler->createFile(NAND_FILENAME) == false)
		throw std::runtime_error("Failed to create file: " NAND_FILENAME);
	
	std::ostringstream oss;
	for (int i = MIN_LBA; i <= MAX_LBA; ++i) {
		oss << std::setfill('0') << std::setw(2) << std::dec << i << '\t'
			<< "0x"
			<< std::setfill('0') << std::setw(8) << std::hex << std::uppercase << 0
			<< '\n';
	}
	std::string formattedData = oss.str();
	fileHandler->writeData(NAND_FILENAME, formattedData);
}

vector<string> NandFlashMemoryImpl::read() {
	vector<string> datas = fileHandler->read(NAND_FILENAME);
	vector<string> ret;
	for (auto data : datas) {
		int pos = data.find("\t");
		ret.push_back(data.substr(pos + 1));
	}
	return ret;
}

string NandFlashMemoryImpl::write(const vector<string>& datas) {
	vector<string> ret;
	for (int i = 0; i < 100; i++) {
		std::ostringstream oss;
		oss << std::setw(2) << std::setfill('0') << std::dec << i << '\t' << datas.at(i);
		ret.push_back(oss.str());
	}
	fileHandler->write(NAND_FILENAME, ret);
	return "";
}