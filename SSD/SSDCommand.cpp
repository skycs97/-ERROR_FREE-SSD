#include "SSDCommand.h"
#include "nand_reader.h"
#include "nand_writer.h"
#include "nand_eraser.h"
#include "nand_flush.h"

using std::string;

/*

bool ReadCommand::parseArg(int argc, const char* argv[])
{
	if (argc != 3) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::READ_CMD);
	parser.setAddr(atoi(argv[ARG_IDX_ADDR]));

	if ((parser.getAddr() < MIN_LBA) || (parser.getAddr() > MAX_LBA)) throw std::invalid_argument("Out of range");

	return true;
}

bool ReadCommand::run()
{
	return true;
}

bool WriteCommand::parseArg(int argc, const char* argv[])
{
	if (argc != 4) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::WRITE_CMD);
	parser.setAddr(atoi(argv[ARG_IDX_ADDR]));

	if ((parser.getAddr() < MIN_LBA) || (parser.getAddr() > MAX_LBA)) throw std::invalid_argument("Out of range");

	parser.parseHexAddress(string(argv[ARG_IDX_DATA]));
	parser.setData(argv[ARG_IDX_DATA]);
	return true;
}

bool WriteCommand::run()
{
	return true;
}

bool EraseCommand::parseArg(int argc, const char* argv[])
{
	if (argc != 4) throw std::invalid_argument("number of argument is incorrect");

	parser.setCmdType(ArgumentParser::ERASE_CMD);

	parser.setEraseStartAddr(atoi(argv[ARG_IDX_ERASE_START_ADDR]));
	if ((parser.getEraseStartAddr() < MIN_LBA) || (parser.getEraseStartAddr() > MAX_LBA)) throw std::invalid_argument("Out of range");

	parser.setEraseCount(atoi(argv[ARG_IDX_ERASE_COUNT]));
	if ((parser.getEraseCount() < 1) || (parser.getEraseCount() > 10)) throw std::invalid_argument("Out of range");
	if ((parser.getEraseStartAddr() + parser.getEraseCount() - 1) > MAX_LBA) throw std::invalid_argument("Out of range");

	return true;
}

bool EraseCommand::run()
{
	return true;
}

bool FlushCommand::parseArg(int argc, const char* argv[])
{
	if (argc != 2) throw std::invalid_argument("number of argument is incorrect");
	parser.setCmdType(ArgumentParser::FLUSH_CMD);

	return true;
}

bool FlushCommand::run()
{
	return true;
}
*/

SSDCommand* SSDCommandFactory::createCommand(const string& cmdName, NandFlashMemory* nandFlashMemory, BufferManager* bufferManager)
{
	if ((cmdName == "R") || (cmdName == "r")) return new NandReader(nandFlashMemory, bufferManager);
	else if ((cmdName == "W") || (cmdName == "w")) return new NandWriter(nandFlashMemory, bufferManager);
	else if ((cmdName == "E") || (cmdName == "e")) return new NandEraser(nandFlashMemory, bufferManager);
	else if ((cmdName == "F") || (cmdName == "f")) return new NandFlush(nandFlashMemory, bufferManager);
	else throw std::invalid_argument("Unknown command type: " + cmdName);

	return nullptr;
}
