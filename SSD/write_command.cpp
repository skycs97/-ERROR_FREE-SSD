#include "write_command.h"
using std::string;
using std::stoi;

void WriteCommand::parseArg(int argc, const char* argv[])
{
	if (argc != WRITE_CORRECT_ARG_SIZE) throw std::invalid_argument("number of argument is incorrect");

	if (isInvalidNumber(string(argv[ARG_IDX_ADDR]))) throw std::invalid_argument("Not a number in address");
	lba = stoi(argv[ARG_IDX_ADDR]);

	if (isInvalidAddress()) throw std::invalid_argument("Out of range");
	
	data = argv[ARG_IDX_DATA];
	validDataOrThrow();
}

bool WriteCommand::isInvalidNumber(const string& str) {
	return (str.find_first_not_of("0123456789") != string::npos);
}

bool WriteCommand::isInvalidHexNumber(const string& str) {
	return (str.find_first_not_of("0123456789ABCDEF") != string::npos);
}

bool WriteCommand::isInvalidAddress() {
	if ((lba < MIN_LBA) || (lba > MAX_LBA)) return true;
	return false;
}

void WriteCommand::validDataOrThrow()
{
	// 0xAAAABBBB : acceptable hexa digit

	if (data.length() != 10) throw std::invalid_argument("Incorrect Hex number length in data");

	std::string cleanedAddress = data;

	if (cleanedAddress.length() > 2 && (cleanedAddress.substr(0, 2) == "0x" || cleanedAddress.substr(0, 2) == "0X")) {
		cleanedAddress = cleanedAddress.substr(2);
		if (isInvalidHexNumber(cleanedAddress)) throw std::invalid_argument("Not a hex number in data");
	}
	else throw std::invalid_argument("Not a hexa digit format in data");
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