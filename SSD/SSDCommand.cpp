#include "SSDCommand.h"
#include "nand_reader.h"
#include "nand_writer.h"
#include "nand_eraser.h"
#include "nand_flush.h"

using std::string;

SSDCommand* SSDCommandFactory::createCommand(const string& cmdName, NandFlashMemory* nandFlashMemory, BufferManager* bufferManager)
{
	if ((cmdName == "R") || (cmdName == "r")) return new NandReader(nandFlashMemory, bufferManager);
	else if ((cmdName == "W") || (cmdName == "w")) return new NandWriter(nandFlashMemory, bufferManager);
	else if ((cmdName == "E") || (cmdName == "e")) return new NandEraser(nandFlashMemory, bufferManager);
	else if ((cmdName == "F") || (cmdName == "f")) return new NandFlush(nandFlashMemory, bufferManager);
	else throw std::invalid_argument("Unknown command type: " + cmdName);

	return nullptr;
}
