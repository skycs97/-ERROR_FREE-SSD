#pragma once
#include "gmock/gmock.h"
#include "FileHandler.h"

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(void, write, (const string&, const vector<string>&), (override));
	MOCK_METHOD(vector<string>, read, (const string&), (override));
};
