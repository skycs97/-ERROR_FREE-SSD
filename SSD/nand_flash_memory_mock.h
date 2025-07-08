#pragma once

#include "gmock/gmock.h"
#include "nand_flash_memory.h"

class NandFlashMemoryMock : public NandFlashMemory {
public:
	MOCK_METHOD(vector<string>, read, (), (override));
	MOCK_METHOD(string, write, (int, int), (override));
};