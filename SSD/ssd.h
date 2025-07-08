#pragma once
#include "nand_reader.h"
#include "nand_writer.h"
#include "OutputHandler.h"

class SSD
{
public:
	SSD(NandReader* reader,
		NandWriter* writer,
		OutputHandler* outputHandler) :
		reader{ reader },
		writer{ writer },
		outputHandler{ outputHandler } {
	}

	void run() {}

private:
	NandReader* reader;
	NandWriter* writer;
	OutputHandler* outputHandler;
};