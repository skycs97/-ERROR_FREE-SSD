#pragma once
#include <string>

using std::string;
#define interface struct

interface Storage{
    virtual string read(int index) = 0;
    virtual string write(int index, int data) = 0;
};
