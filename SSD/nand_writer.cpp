#include "nand_writer.h"

string NandWriter::write(int lba, string data)
{
	if (BUFFER_ENABLE) {
		bufferManager->addWriteCommand(lba, data);
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}

bool NandWriter::parseArg(int argc, const char* argv[])
{
	if (argc != 4) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::WRITE_CMD);
	parser.setAddr(atoi(argv[ARG_IDX_ADDR]));

	if ((parser.getAddr() < MIN_LBA) || (parser.getAddr() > MAX_LBA)) throw std::invalid_argument("Out of range");

	parser.parseHexAddress(string(argv[ARG_IDX_DATA]));
	parser.setData(argv[ARG_IDX_DATA]);
	return true;
}

string NandWriter::run()
{
	int addr = parser.getAddr();
	string data = parser.getData();

	return write(addr, data);
}
