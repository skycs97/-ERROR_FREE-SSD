#pragma once
#include "gmock/gmock.h"
#include "file_handler.h"

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(bool, checkExistNandFile, (const string&), (override));
	MOCK_METHOD(void, createInitNandFile, (const string&), (override));
	MOCK_METHOD(void, write, (const string&, const vector<string>&), (override));
	MOCK_METHOD(vector<string>, read, (const string&), (override));
};
