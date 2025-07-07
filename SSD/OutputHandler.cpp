#include "gmock/gmock.h"
#include "FileHandler.h"
#include "OutputHandler.h"

#include <string>

void OutputHandler::output(const string& output_string) {
	fileHandler->write(output_string);
}

string OutputHandler::read(void) {
	return fileHandler->read();
}

