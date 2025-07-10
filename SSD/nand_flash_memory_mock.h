#pragma once

#include "gmock/gmock.h"
#include "nand_flash_memory.h"

class NandFlashMemoryMock : public NandFlashMemory {
public:
	MOCK_METHOD(void, init, (), (override));
	MOCK_METHOD(vector<string>, read, (), (override));
	MOCK_METHOD(string, write, (const vector<string>&), (override));
};