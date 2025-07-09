#pragma once
#include "gmock/gmock.h"
#include "file_handler.h"

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(bool, checkExistNandFile, (const string&), (override));
	MOCK_METHOD(void, createInitNandFile, (const string&), (override));
	MOCK_METHOD(void, write, (const string&, const vector<string>&), (override));
	MOCK_METHOD(vector<string>, read, (const string&), (override));
	MOCK_METHOD(void, createDirIfNotExist, (const string&), (override));
	MOCK_METHOD(bool, isExist, (const string&, const string&), (override));
	MOCK_METHOD(void, createEmptyFile, (const string&), (override));
	MOCK_METHOD(void, rename, (const string&, const string&), (override, const));
	MOCK_METHOD(vector<string>, findFileUsingPrefix, (const string&, const string&), (override));

};
