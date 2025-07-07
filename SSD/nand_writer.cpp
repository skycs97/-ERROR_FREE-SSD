#include "nand_writer.h"

string NandWriter::write(int lba, int data)
{
	return nandFlashMemory->write(lba, data);
}