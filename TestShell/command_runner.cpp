#include <stdexcept>
#include "command_runner.h"
#include "logger.h"

string CommandRunner::read(const string& LBA) const
{
	AssertionCheckSsdInterface();

	string result = ssdInterface->read(LBA);

	LOGGING_SHELL( "LBA :" + LBA + ", Result : " + result);
	return result;
}

void CommandRunner::AssertionCheckSsdInterface() const
{
	if (isSetSsdInterface() == false) {
		throw std::runtime_error("ssd Interface hasn't set");
	}
}

string CommandRunner::write(const string& LBA, const string& value) const
{
	AssertionCheckSsdInterface();

	string result = ssdInterface->write(LBA, value);

	LOGGING_SHELL( "LBA :" +LBA+ " , Result : " + result);
	return result;
}

string CommandRunner::flush() const
{
	AssertionCheckSsdInterface();

	string result = ssdInterface->flush();

	LOGGING_SHELL( "Result : " + result);
	return result;
}

string CommandRunner::erase(const string& startLBA, const string& LBARange) const
{
	if (LBARange == "0") { return "ERROR"; }

	AssertionCheckSsdInterface();

	int startIndexNum = stoi(startLBA);
	int rangeNum = stoi(LBARange);
	string result = "";

	while (rangeNum > MAX_ERASE_RANGE) {
		result = ssdInterface->erase(std::to_string(startIndexNum), std::to_string(MAX_ERASE_RANGE));

		startIndexNum += MAX_ERASE_RANGE;
		rangeNum -= MAX_ERASE_RANGE;
	}

	if (rangeNum > 0) {
		result = ssdInterface->erase(std::to_string(startIndexNum), std::to_string(rangeNum));
	}

	LOGGING_SHELL( "startLBA :" + startLBA + " , LBARange : " + LBARange + ", Result : " + result);
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

