#include "command_runner.h"
#include <stdexcept>
string CommandRunner::read(const string& LBA) const
{
	if (isSetSsdInterface() == false) {
		throw std::runtime_error("ssd Interface hasn't set");
	}

	string result = ssdInterface->read(LBA);

	return result;
}

string CommandRunner::write(const string& LBA, const string& value) const
{
	if (isSetSsdInterface() == false) {
		throw std::runtime_error("ssd Interface hasn't set");
	}

	string result = ssdInterface->write(LBA, value);

	return result;
}

bool CommandRunner::isSetSsdInterface() const
{
	return ssdInterface != nullptr;
}

void CommandRunner::setStorage(SsdInterface* ssdInterface)
{
	this->ssdInterface = ssdInterface;
}

