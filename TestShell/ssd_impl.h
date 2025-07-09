#pragma once
#include "ssd_interface.h"

class SsdImpl : public SsdInterface {
public:
	string read(const string& index) override;
	string write(const string& index, const string& data) override;
	string erase(const string& startIndex, const string& range) override;

	string flush() override;
private:
	const string ssdOutputPath = "ssd_output.txt";
	const string ssdExcutable = R"(..\x64\Release\ssd.exe)";
	static const int MAX_ERASE_RANGE = 10;
};