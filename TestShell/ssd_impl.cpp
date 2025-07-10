#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "ssd_impl.h"
#include "TEST_SHELL_CONFIG.h"

string SsdImpl::read(const string& LBA)
{
    string cmd = makeReadCommand(LBA);

    return executeSsd(cmd);
}

string SsdImpl::write(const string& LBA, const string& data)
{
    string cmd = makeWriteCommand(LBA, data);

    return executeSsd(cmd);
}

string SsdImpl::erase(const string& startLBA, const string& range)
{
    int rangeNum = stoi(range);

    if (rangeNum > MAX_ERASE_RANGE) {
        return ERROR;
    }

    string cmd = makeEraseCommand(startLBA, range);
    system(cmd.c_str());

    return executeSsd(cmd);
}

string SsdImpl::flush() {
    string cmd = makeFlushCommand();

    return executeSsd(cmd);
}

std::string SsdImpl::cmdJoin(std::vector<std::string> const& strings)
{
    std::string delim = " ";
    std::stringstream ss;
    std::copy(strings.begin(), strings.end(),
        std::ostream_iterator<std::string>(ss, delim.c_str()));

    return ss.str();
}

string SsdImpl::makeReadCommand(const string& LBA) {
    vector<string> cmds;
    cmds.push_back(ssdExcutable);
    cmds.push_back("R");
    cmds.push_back(LBA);

    return cmdJoin(cmds);
}

string SsdImpl::makeWriteCommand(const string& LBA, const string& data) {
    vector<string> cmds;

    cmds.push_back(ssdExcutable);
    cmds.push_back("W");
    cmds.push_back(LBA);
    cmds.push_back(data);

    return cmdJoin(cmds);
}

string SsdImpl::makeEraseCommand(const string& startLBA, const string& range) {
    vector<string> cmds;

    cmds.push_back(ssdExcutable);
    cmds.push_back("E");
    cmds.push_back(startLBA);
    cmds.push_back(range);

    return cmdJoin(cmds);
}

string SsdImpl::makeFlushCommand() {
    vector<string> cmds;

    cmds.push_back(ssdExcutable);
    cmds.push_back("F");

    return cmdJoin(cmds);
}

string SsdImpl::executeSsd(string ssdCmd) {
    int processRet = system(ssdCmd.c_str());

    return checkSsdResult();
}

string SsdImpl::checkSsdResult() {
    std::ifstream inputFile(ssdOutputPath);
    std::string line;

    if (inputFile.is_open() == false) {
        return ERROR;
    }

    getline(inputFile, line);
    inputFile.close();

    return line;
}

