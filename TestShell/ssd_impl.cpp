#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "ssd_impl.h"
#include "TEST_SHELL_CONFIG.h"

string SsdImpl::read(const string& index)
{
	string cmd = ssdExcutable + " R " + index;

	int processRet = system(cmd.c_str());

    // �б� ���� ���� ����
    std::ifstream inputFile(ssdOutputPath);
    std::string line;

    if (inputFile.is_open() == false) {
        return ERROR;
    }
    getline(inputFile, line);
    inputFile.close();

    return line;
}

string SsdImpl::write(const string& index, const string& data)
{
    string cmd = ssdExcutable + " W " + index + " " + data;

    int processRet = system(cmd.c_str());

    // �б� ���� ���� ����
    std::ifstream inputFile(ssdOutputPath);
    std::string line;

    if (inputFile.is_open() == false) {
        return ERROR;
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

    // �б� ���� ���� ����
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
    string cmd = ssdExcutable + " F";

    int processRet = system(cmd.c_str());

    // �б� ���� ���� ����
    std::ifstream inputFile(ssdOutputPath);
    std::string line;

    if (inputFile.is_open() == false) {
        return ERROR;
    }
    getline(inputFile, line);
    inputFile.close();

    return line;
}