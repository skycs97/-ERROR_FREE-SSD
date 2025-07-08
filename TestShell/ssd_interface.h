#pragma once
#include <string>

using std::string;
#define interface struct

interface SsdInterface{
    virtual string read(const string& index) = 0;
    virtual string write(const string& index, const string& data) = 0;
};
