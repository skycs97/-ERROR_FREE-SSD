#include "write_command.h"

string WriteCommand::write(int lba, string data)
{
	if (BUFFER_ENABLE) {
		bufferManager->addWriteCommand(lba, data);
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}

bool WriteCommand::parseArg(int argc, const char* argv[])
{
	if (argc != WRITE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(CMD_WRITE);
	parser.setLBA(atoi(argv[ARG_IDX_ADDR]));

	if (isInvalidAddress(parser.getLBA())) throw std::invalid_argument("Out of range");

	parser.parseHexAddress(string(argv[ARG_IDX_DATA]));
	parser.setData(argv[ARG_IDX_DATA]);
	return true;
}

bool WriteCommand::isInvalidAddress(int nLBA) {
	if ((nLBA < MIN_LBA) || (nLBA > MAX_LBA)) return true;
	return false;
}

string WriteCommand::run()
{
	int addr = parser.getLBA();
	string data = parser.getData();

	return write(addr, data);
}
