#include "ssd_command.h"
#include "read_command.h"
#include "write_command.h"
#include "erase_command.h"
#include "flush_command.h"

using std::string;

SSDCommand* SSDCommandFactory::createCommand(const string& cmdName, NandFlashMemory* nandFlashMemory, BufferManager* bufferManager)
{
	if (isReadCmd(cmdName)) return new ReadCommand(nandFlashMemory, bufferManager);
	else if (isWriteCmd(cmdName)) return new WriteCommand(nandFlashMemory, bufferManager);
	else if (isEraseCmd(cmdName)) return new EraseCommand(nandFlashMemory, bufferManager);
	else if (isFlushCmd(cmdName)) return new FlushCommand(nandFlashMemory, bufferManager);
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