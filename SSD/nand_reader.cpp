#include "nand_reader.h"
#include "global_config.h"
#include <stdexcept>
string NandReader::read(int LBA)
{
	if (LBA < MIN_LBA || LBA > MAX_LBA) throw std::range_error("The LBA must be a value between 0 and 99.\n");
	vector<string> datas = nandFlashMemory->read();
	return datas.at(LBA);
}
