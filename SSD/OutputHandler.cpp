#include "gmock/gmock.h"
#include "FileHandler.h"
#include "OutputHandler.h"

#include <string>

void OutputHandler::output(const string& output_string) {
	fileHandler->write(OUTPUT_FILENAME, { output_string });
}