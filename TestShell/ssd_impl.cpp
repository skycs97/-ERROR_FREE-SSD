#include <cstdlib>
#include <fstream>
#include <iostream>
#include "ssd_impl.h"

string SsdImpl::read(const string& index)
{
	string cmd = ssdExcutable + " R " + index;

	int processRet = system(cmd.c_str());

    // 읽기 모드로 파일 열기
    std::ifstream inputFile(ssdOutputPath);
    std::string line;

    if (inputFile.is_open() == false) {
        return "Error";
    }
    getline(inputFile, line);
    inputFile.close();

    return line;
}

string SsdImpl::write(const string& index, const string& data)
{
    string cmd = ssdExcutable + " W " + index + " " + data;

    int processRet = system(cmd.c_str());

    // 읽기 모드로 파일 열기
    std::ifstream inputFile(ssdOutputPath);
    std::string line;

    if (inputFile.is_open() == false) {
        return "Error";
    }
    getline(inputFile, line);
    inputFile.close();

    return line;
}
