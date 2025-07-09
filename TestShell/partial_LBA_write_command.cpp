#include "partial_LBA_write_command.h"

bool PartialLBAWrite::checkResult(const vector<std::string>& result) const
{
	string firstItem = result[0];

	for (const std::string& resultitem : result)
	{
		if (resultitem != firstItem) { return false; }
	}
	return true;
}

void PartialLBAWrite::run(const CommandRunner& cmdRunner) const
{
	for (int testRepeat = 0; testRepeat < REPEAT_COUNT; testRepeat++) {
		vector<std::string> result;

		for (std::string Lba : TestLbaList) {
			cmdRunner.write(Lba, WRITE_DATA);
		}

		for (std::string Lba : TestLbaList) {

			result.push_back(cmdRunner.read(Lba));
		}

		if (checkResult(result) == false) {
			throw TestScriptFailExcpetion("Fail");
		}
	}

	std::cout << "Pass" << std::endl;
}

void PartialLBAWrite::printHelp() const
{
	std::cout << "** Partial LBA Write Command **\n";
	std::cout << " - Write a specific value to several LBAs and then read it to check the value.\n";
	std::cout << "Usage\n";
	std::cout << " 2_PartialLBAWrite\n";
	std::cout << " 2_\n";
}
