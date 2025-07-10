#pragma once
#include <windows.h>
#include <iostream>
#include "ssd_interface.h"
#include <vector>

class SsdImpl : public SsdInterface {
public:
	string read(const string& LBA) override;
	string write(const string& LBA, const string& data) override;
	string erase(const string& startLBA, const string& range) override;
	SsdImpl() {
		string exeEnvVS[2] = { R"(..\x64\Release\SSD.exe)", R"(.\ssd_output.txt)" };
		string exeEnvEXE[2] = { R"(.\SSD.exe)", R"(.\ssd_output.txt)" };

		if (FileExists(exeEnvVS[0])) {
			ssdExcutable = exeEnvVS[0];
			ssdOutputPath = exeEnvVS[1];
		}
		else if (FileExists(exeEnvEXE[0])) {
			ssdExcutable = exeEnvEXE[0];
			ssdOutputPath = exeEnvEXE[1];
		}
		else {
			throw std::runtime_error("Cannot find SSD.exe");
		}
	}

	string flush() override;

	string executeSsd(string ssdCmd);
	string checkSsdResult();
private:
	string ssdOutputPath;
	string ssdExcutable;
	static const int MAX_ERASE_RANGE = 10;

	string makeReadCommand(const string& LBA);
	string makeWriteCommand(const string& LBA, const string& data);
	string makeEraseCommand(const string& startLBA, const string& range);
	string makeFlushCommand();

	std::string cmdJoin(std::vector<std::string> const& strings);
	bool FileExists(const std::string& path) {
		DWORD attrib = GetFileAttributesA(path.c_str());
		return (attrib != INVALID_FILE_ATTRIBUTES) && !(attrib & FILE_ATTRIBUTE_DIRECTORY);
	}
};
