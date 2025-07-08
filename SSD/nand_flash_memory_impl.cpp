#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "nand_flash_memory_impl.h"

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
		oss << i << '\t' << datas.at(i);
		ret.push_back(oss.str());
	}
	fileHandler->write(NAND_FILENAME, ret);
	return "";
}