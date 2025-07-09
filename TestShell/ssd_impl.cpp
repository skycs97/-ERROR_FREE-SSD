#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
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

string SsdImpl::erase(const string& startIndex, const string& range)
{
    int rangeNum = stoi(range);
    int startIndexNum = stoi(startIndex);
    string cmd;

    // 읽기 모드로 파일 열기
    std::ifstream inputFile(ssdOutputPath);
    std::string line;

    if (inputFile.is_open() == false) {
        return "Error";
    }
    if (rangeNum > MAX_ERASE_RANGE) {
        return "Error";
    }

    cmd = ssdExcutable + " E " + std::to_string(startIndexNum) + " " + std::to_string(rangeNum);
    system(cmd.c_str());

    inputFile.close();

    return line;
}

string SsdImpl::flush() {
    return "";
}