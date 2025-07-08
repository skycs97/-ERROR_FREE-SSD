#include "full_write_and_read_compare_command.h"

void FullWriteAndReadCompare::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	int lba = 0;
	int testSize = 5;
	std::vector<string> testValue = { "0xA5A5A5A5", "0x5A5A5A5A", "0xFFFFFFFF", "0xF0F0F0F0", "0x0F0F0F0F" };
	string writeSuccess = "";
	string res;

	while (lba <= MAX_LBA) {
		for (int i = 0; i < testSize; i++) {
			if (writeSuccess == (res = cmdRunner.write(std::to_string(lba + i), testValue[0])))
				continue;
			result.push_back(res);
		}

		for (int i = 0; i < testSize; i++) {
			if (testValue[0] == (res = cmdRunner.read(std::to_string(lba + i))))
				continue;
			result.push_back(res);
		}

		lba += testSize;

		for (int i = 0; i < testSize; i++) {
			if (writeSuccess == (res = cmdRunner.write(std::to_string(lba + i), testValue[i])))
				continue;
			result.push_back(res);
		}

		for (int i = 0; i < testSize; i++) {
			if (testValue[i] == (res = cmdRunner.read(std::to_string(lba + i))))
				continue;
			result.push_back(res);
		}

		lba += testSize;
	}

	if (result.size())
		std::cout << "FullWriteAndReadCompare Fail" << std::endl;
	else
		std::cout << "FullWriteAndReadCompare Pass" << std::endl;
}

void FullWriteAndReadCompare::printHelp() const
{
}
