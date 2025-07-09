#include "write_command.h"

void WriteCommand::parseArg(int argc, const char* argv[])
{
	if (argc != WRITE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");
	lba = atoi(argv[ARG_IDX_ADDR]);

	if (isInvalidAddress()) throw std::invalid_argument("Out of range");

	parser.parseHexAddress(string(argv[ARG_IDX_DATA]));
	data = argv[ARG_IDX_DATA];
}

bool WriteCommand::isInvalidAddress() {
	if ((lba < MIN_LBA) || (lba > MAX_LBA)) return true;
	return false;
}

string WriteCommand::run()
{
	if (BUFFER_ENABLE) {
		bufferManager->addWriteCommand(lba, data);
		return "";
	}

	vector<string> datas = nandFlashMemory->read();
	datas[lba] = data;
	return nandFlashMemory->write(datas);
}