#include "write_read_aging_command.h"
#include <random>  
#include <chrono> 
#include <iomanip>
#include <sstream>
#include "command_runner.h"

void WriteReadAging::run(const CommandRunner& cmdRunner) const
{
	std::vector<string> result;
	string writeSuccess = "";
	string res;

	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<unsigned int> distribution(
		std::numeric_limits<unsigned int>::min(),
		std::numeric_limits<unsigned int>::max()
	);

	for (int i = 0; i < 200; i++) {
		unsigned int random_value = distribution(generator);
		std::stringstream ss;
		ss << "0x" << std::hex
			<< std::uppercase
			<< std::setw(8) << std::setfill('0')
			<< random_value;

		std::string hex_string = ss.str();

		if (writeSuccess != (res = cmdRunner.write("0", hex_string)))
			result.push_back(res);

		if (writeSuccess != (res = cmdRunner.write("99", hex_string)))
			result.push_back(res);

		if (cmdRunner.read("0") != cmdRunner.read("99"))
			result.push_back(res);
	}

	if (result.size())
		throw TestScriptFailExcpetion("Fail");

	std::cout << "Pass" << std::endl;
}

void WriteReadAging::printHelp() const
{
	std::cout << "** Write Read Aging Command **\n";
	std::cout << " - A test that writes a random value to LBA 0 and 99 and then reads it to confirm, repeated 200 times..\n";
	std::cout << "Usage\n";
	std::cout << " 3_WriteReadAging\n";
	std::cout << " 3_\n";
}
