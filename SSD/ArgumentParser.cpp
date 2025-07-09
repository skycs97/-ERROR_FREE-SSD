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

// stoul���� ��ȯ ���� �� std::invalid_argument ����, ���� �ʰ� �� std::out_of_range ���ܸ� �߻�
unsigned long ArgumentParser::parseHexAddress(const std::string& hexAddress)
{
	// "0x" ���λ縦 ���� (std::stoul�� �ڵ����� ó��������, ��������� �����ص� ����)
	std::string cleanedAddress = hexAddress;
	if (cleanedAddress.length() > 2 && (cleanedAddress.substr(0, 2) == "0x" || cleanedAddress.substr(0, 2) == "0X")) {
		cleanedAddress = cleanedAddress.substr(2);
	}
	return std::stoul(cleanedAddress, nullptr, 16);
}