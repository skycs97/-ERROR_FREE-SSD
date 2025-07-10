#pragma once
#include "gmock/gmock.h"
#include "file_handler.h"

class FileHandlerMock : public FileHandler {
public:
	MOCK_METHOD(void, createDirectory, (const string&), (override));
	MOCK_METHOD(void, createFile, (const string&), (override));
	MOCK_METHOD(char*, readFile, (const string&), (override));
	MOCK_METHOD(void, writeData, (const string&, const string&), (override));
	MOCK_METHOD(void, rename, (const string&, const string&), (override, const));
	MOCK_METHOD(bool, isFileExistByMatchLength, (const string&, const string&, int), (override));
	MOCK_METHOD(vector<string>, getFileUsingPrefix, (const string&, const string&), (override));
};
