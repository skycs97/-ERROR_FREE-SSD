#include <random>  
#include <chrono> 
#include <iomanip>
#include <sstream>
#include "command_runner.h"
#include "write_read_aging_command.h"

void WriteReadAging::run(const CommandRunner& cmdRunner) const
{
	string lba0 = "0";
	string lba99 = "99";
	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<unsigned int> distribution(
		std::numeric_limits<unsigned int>::min(),
		std::numeric_limits<unsigned int>::max()
	);

	for (int i = 0; i < 200; i++) {

		string data = hexToString(distribution(generator));

		if (WRITESUCCESS != cmdRunner.write(lba0, data))
			throw TestScriptFailExcpetion(FAIL);

		if (WRITESUCCESS != cmdRunner.write(lba99, data))
			throw TestScriptFailExcpetion(FAIL);

		if (cmdRunner.read(lba0) != cmdRunner.read(lba99))
			throw TestScriptFailExcpetion(FAIL);
	}

	std::cout << "Pass" << std::endl;
}

string WriteReadAging::hexToString(unsigned int random_value) const
{
	std::stringstream ss;
	ss << "0x" << std::hex
		<< std::uppercase
		<< std::setw(8) << std::setfill('0')
		<< random_value;

	return ss.str();
}

void WriteReadAging::printHelp() const
{
	std::cout << "** Write Read Aging Command **\n";
	std::cout << " - A test that writes a random value to LBA 0 and 99 and then reads it to confirm, repeated 200 times..\n";
	std::cout << "Usage\n";
	std::cout << " 3_WriteReadAging\n";
	std::cout << " 3_\n";
}
