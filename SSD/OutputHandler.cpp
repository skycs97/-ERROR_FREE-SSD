#include "gmock/gmock.h"
#include "OutputHandler.h"

#include <string>
#include <fstream>

using std::string;
using std::ofstream;


void OutputHandler::output(const string& output_string) {
	file.open(OUTPUT_FILENAME);
	file << output_string;
	file.close();
}

