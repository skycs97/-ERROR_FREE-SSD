#include "gmock/gmock.h"
#include "file_handler.h"
#include "output_handler.h"

#include <string>

void OutputHandler::output(const string& output_string) {
	fileHandler->write(OUTPUT_FILENAME, { output_string });
}