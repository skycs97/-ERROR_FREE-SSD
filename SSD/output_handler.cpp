#include "gmock/gmock.h"
#include "file_handler.h"
#include "output_handler.h"

#include <string>

void OutputHandler::init()
{
	fileHandler->createFile(OUTPUT_FILENAME);
}

void OutputHandler::output(const string& output_string) {
	fileHandler->writeData(OUTPUT_FILENAME, { output_string });
}