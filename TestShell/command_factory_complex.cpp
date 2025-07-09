#include <sstream>
#include "command_factory_complex.h"

void CommandFactoryComplex::addFactory(const string& cmdName, CommandFactory* factory)
{
	this->factoryComplex.insert({ cmdName, factory });
}

CommandFactory* CommandFactoryComplex::getFactory(const string& cmdName)
{
	if (find(AVAILABLE_COMMAND_LIST.begin(), AVAILABLE_COMMAND_LIST.end(), cmdName) 
		== AVAILABLE_COMMAND_LIST.end()) {
		return nullptr;
	}

	return this->factoryComplex.at(cmdName);
}

std::shared_ptr<Command> CommandFactoryComplex::makeCommand(const string& cmdName, const vector<string>& args) {
	auto factory = getFactory(cmdName);
	
	if (factory == nullptr) {
		return nullptr;
	}

	return factory->makeCommand(cmdName, args);
}
