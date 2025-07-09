#include "SSDCommand.h"
#include "nand_reader.h"
#include "nand_writer.h"
#include "nand_eraser.h"
#include "nand_flush.h"

using std::string;

SSDCommand* SSDCommandFactory::createCommand(const string& cmdName, NandFlashMemory* nandFlashMemory, BufferManager* bufferManager)
{


	if (isReadCmd(cmdName)) return new NandReader(nandFlashMemory, bufferManager);
	else if (isWriteCmd(cmdName)) return new NandWriter(nandFlashMemory, bufferManager);
	else if (isEraseCmd(cmdName)) return new NandEraser(nandFlashMemory, bufferManager);
	else if (isFlushCmd(cmdName)) return new NandFlush(nandFlashMemory, bufferManager);
	else throw std::invalid_argument("Unknown command type: " + cmdName);

	return nullptr;
}

bool SSDCommandFactory::isReadCmd(const string& cmdName)
{
	return (cmdName == string("R")) || (cmdName == string("r"));
}

bool SSDCommandFactory::isWriteCmd(const string& cmdName)
{
	return (cmdName == string("W")) || (cmdName == string("w"));
}

bool SSDCommandFactory::isEraseCmd(const string& cmdName)
{
	return (cmdName == string("E")) || (cmdName == string("e"));
}

bool SSDCommandFactory::isFlushCmd(const string& cmdName)
{
	return (cmdName == string("F")) || (cmdName == string("f"));
}