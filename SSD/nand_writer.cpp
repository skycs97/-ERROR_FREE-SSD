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
	if (argc != WRITE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::WRITE_CMD);
	parser.setLBA(atoi(argv[ARG_IDX_ADDR]));

	if (isInvalidAddress(parser.getLBA())) throw std::invalid_argument("Out of range");

	parser.parseHexAddress(string(argv[ARG_IDX_DATA]));
	parser.setData(argv[ARG_IDX_DATA]);
	return true;
}

bool NandWriter::isInvalidAddress(int nLBA) {
	if ((nLBA < MIN_LBA) || (nLBA > MAX_LBA)) return true;
	return false;
}

string NandWriter::run()
{
	int addr = parser.getLBA();
	string data = parser.getData();

	return write(addr, data);
}
