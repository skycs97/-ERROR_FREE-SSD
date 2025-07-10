#pragma once
#include "ssd_interface.h"
#include <vector>

class SsdImpl : public SsdInterface {
public:
	string read(const string& LBA) override;
	string write(const string& LBA, const string& data) override;
	string erase(const string& startLBA, const string& range) override;
	string flush() override;

	string executeSsd(string ssdCmd);
	string checkSsdResult();
private:
	const string ssdOutputPath = "ssd_output.txt";
	const string ssdExcutable = R"(..\x64\Release\ssd.exe)";
	static const int MAX_ERASE_RANGE = 10;

	string makeReadCommand(const string& LBA);
	string makeWriteCommand(const string& LBA, const string& data);
	string makeFlushCommand();

	std::string cmdJoin(std::vector<std::string> const& strings);
};