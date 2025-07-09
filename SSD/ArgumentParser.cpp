#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "ArgumentParser.h"

using std::string;

int ArgumentParser::getEraseStartLBA() {
	return nEraseStartLBA; 
}

int ArgumentParser::getEraseLBACount() {
	return nEraseLBACount; 
}

void ArgumentParser::setCmdType(CMD_TYPE cmdType) { 
	eCmd = cmdType; 
}

void ArgumentParser::setLBA(int addr) { 
	nLBA = addr; 
}

void ArgumentParser::setData(const string& data) { 
	strData = data; 
}

void ArgumentParser::setEraseStartLBAAddr(int startAddr) { 
	nEraseStartLBA = startAddr; 
}

void ArgumentParser::setEraseLBACount(int nCount) { 
	nEraseLBACount = nCount; 
}

ArgumentParser::CMD_TYPE ArgumentParser::getCmdType()
{
	return eCmd;
}

int ArgumentParser::getLBA()
{
	return nLBA;
}

int ArgumentParser::getLBACount()
{
	return nLBACount;
}

string ArgumentParser::getData()
{
	return strData;
}

// stoul에서 변환 실패 시 std::invalid_argument 예외, 범위 초과 시 std::out_of_range 예외를 발생
unsigned long ArgumentParser::parseHexAddress(const std::string& hexAddress)
{
	// "0x" 접두사를 제거 (std::stoul은 자동으로 처리하지만, 명시적으로 제거해도 무방)
	std::string cleanedAddress = hexAddress;
	if (cleanedAddress.length() > 2 && (cleanedAddress.substr(0, 2) == "0x" || cleanedAddress.substr(0, 2) == "0X")) {
		cleanedAddress = cleanedAddress.substr(2);
	}
	return std::stoul(cleanedAddress, nullptr, 16);
}