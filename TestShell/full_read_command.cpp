#include <iomanip>
#include "full_read_command.h"

void FullReadCommand::run(const CommandRunner& cmdRunner) const
{
	string result;
	std::cout << "[Full Read]" << std::endl;
	for (int lba = MIN_LBA; lba <= MAX_LBA; lba++) {
		result = cmdRunner.read(std::to_string(lba));
		printResult(result, std::to_string(lba));
	}
}
void FullReadCommand::printResult(const string& result, const string& lba) const
{
	std::cout << "LBA " << std::setw(2) << std::setfill('0') << lba << " : ";
	std::cout << result << std::endl;
}

void FullReadCommand::printHelp() const
{
	std::cout << "** Full Read Command **\n";
	std::cout << " - Read value from the all LBAs in SSD.\n";
	std::cout << " - LBA (" << MIN_LBA << " ~ " << MAX_LBA << ")\n\n";
	std::cout << "Usage\n";
	std::cout << " fullread\n";
}
