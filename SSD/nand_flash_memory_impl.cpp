#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "nand_flash_memory_impl.h"



void NandFlashMemoryImpl::init()
{
	if (fileHandler->isFileExistByMatchLength(".\\*", NAND_FILENAME, strlen(NAND_FILENAME))) return;

	fileHandler->createFile(NAND_FILENAME);
	fileHandler->writeData(NAND_FILENAME, getRawDataFormatForNandWrite(nullptr));
}

vector<string> NandFlashMemoryImpl::read() {
	return convertToVectorStringFormat(fileHandler->readFile(NAND_FILENAME));
}

string NandFlashMemoryImpl::write(vector<string>& datas) {
	fileHandler->writeData(NAND_FILENAME, getRawDataFormatForNandWrite(&datas));
	return "";
}

vector<string> NandFlashMemoryImpl::convertToVectorStringFormat(const char* data) {
	vector<string> lines;
	std::istringstream iss(data);
	string line;

	while (std::getline(iss, line)) {
		lines.push_back(line.substr(line.find('\t') + 1));
	}

	removeLastSpaceChar(lines);
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

string NandFlashMemoryImpl::getRawDataFormatForNandWrite(vector<string>* datas)
{
	if(datas != nullptr)
		removeLastSpaceChar(*datas);

	std::ostringstream oss;
	for (int i = MIN_LBA; i <= MAX_LBA; ++i) {
		string value = datas == nullptr ? "0x00000000" : (*datas)[i];
		oss << std::setw(2) << std::setfill('0') << std::dec << i << '\t'
			<< value << '\n';
	}
	
	return oss.str();
}