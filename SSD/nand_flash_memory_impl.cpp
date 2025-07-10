#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "nand_flash_memory_impl.h"



void NandFlashMemoryImpl::init()
{
	if (fileHandler->isFileExistByMatchLength(".\\*", NAND_FILENAME, strlen(NAND_FILENAME))) return;

	fileHandler->createFile(NAND_FILENAME);
	
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
	char* read_buf = fileHandler->readFile(NAND_FILENAME);
	vector<string> datas = convertToVectorStringFormat(read_buf);
	removeLastSpaceChar(datas);

	return datas;
}

string NandFlashMemoryImpl::write(vector<string>& datas) {
	removeLastSpaceChar(datas);
	
	std::ostringstream oss;	
	for (int i = MIN_LBA; i <= MAX_LBA; ++i) {
		oss << std::setfill('0') << std::setw(2) << std::dec << i << '\t'
			<< std::setfill('0') << std::setw(8) << std::hex << std::uppercase << datas.at(i)
			<< '\n';
	}

	std::string formattedData = oss.str();
	fileHandler->writeData(NAND_FILENAME, formattedData);
	return "";
}

vector<string> NandFlashMemoryImpl::convertToVectorStringFormat(const char* data) {
	vector<string> lines;
	std::istringstream iss(data);
	string line;

	while (std::getline(iss, line)) {
		lines.push_back(line.substr(line.find('\t') + 1));
	}

	return lines;
}

void NandFlashMemoryImpl::removeLastSpaceChar(vector<string>& datas)
{
	for (string& data : datas)
	{
		while (!data.empty() && (data.back() == '\n' || data.back() == '\r')) {
			data.pop_back();
		}
	}
}