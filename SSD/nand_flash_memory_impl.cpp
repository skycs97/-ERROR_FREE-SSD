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

string NandFlashMemoryImpl::write(const vector<string>& data) {
	return "";
}