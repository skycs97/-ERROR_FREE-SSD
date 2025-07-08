#include "command_runner.h"
#include <stdexcept>
string CommandRunner::read(const string& LBA)
{
	if (ssdInterface == nullptr) {
		throw std::runtime_error("ssd Interface hasn't set");
	}

	string result = ssdInterface->read(LBA);

	return result;
}

string CommandRunner::write(const string& LBA, const string& value)
{
	if (ssdInterface == nullptr) {
		throw std::runtime_error("ssd Interface hasn't set");
	}
	
	string result = ssdInterface->write(LBA, value);

	return result;
}

void CommandRunner::setStorage(SsdInterface* ssdInterface)
{
	this->ssdInterface = ssdInterface;
}

