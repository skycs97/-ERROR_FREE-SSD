#pragma once
#include "read_command.h"
#include "erase_command.h"
#include "erase_range_command.h"
#include "write_command.h"
#include "exit_command.h"
#include "help_command.h"

#include "full_read_command.h"
#include "full_write_command.h"

#include "flush_command.h"

#include "full_write_and_read_compare_command.h"
#include "partial_LBA_write_command.h"
#include "write_read_aging_command.h"
#include "erase_and_write_aging.h"

#include <map>

struct CommandInfo {
public:
	std::string name;
	std::string helpStr;
	CommandFactory* factory;

	CommandInfo(const std::string& name, const std::string& helpStr, CommandFactory* factory)
		: name(name), helpStr(helpStr), factory(factory)
	{
	}
};
namespace {
    CommandInfo CMD_HELP_INFO = { CMD_HELP, CMD_HELP_HELP, new HelpCommandFactory() };
    CommandInfo CMD_READ_INFO = { CMD_READ, CMD_READ_HELP, new ReadCommandFactory() };
    CommandInfo CMD_WRITE_INFO = { CMD_WRITE, CMD_WRITE_HELP, new WriteCommandFactory() };
    CommandInfo CMD_EXIT_INFO = { CMD_EXIT, CMD_EXIT_HELP, new ExitCommandFactory() };
    CommandInfo CMD_FULLWRITE_INFO = { CMD_FULLWRITE, CMD_FULLWRITE_HELP, new FullWriteCommandFactory() };
    CommandInfo CMD_FULLREAD_INFO = { CMD_FULLREAD, CMD_FULLREAD_HELP, new FullReadCommandFactory() };
    CommandInfo CMD_FLUSH_INFO = { CMD_FLUSH, CMD_FLUSH_HELP, new FlushCommandFactory() };
    CommandInfo CMD_1_FULL_WRITE_AND_READ_COMPARE_INFO = {
        CMD_1_FULL_WRITE_AND_READ_COMPARE,
        CMD_1_FULL_WRITE_AND_READ_COMPARE_HELP,
        new FullWriteAndReadCompareCommandFactory()
    };
    CommandInfo CMD_2_PARTIAL_LBA_WRITE_INFO = {
        CMD_2_PARTIAL_LBA_WRITE,
        CMD_2_PARTIAL_LBA_WRITE_HELP,
        new PartialLBAWriteCommandFactory()
    };
    CommandInfo CMD_3_WRITE_READ_AGING_INFO = {
        CMD_3_WRITE_READ_AGING,
        CMD_3_WRITE_READ_AGING_HELP,
        new WriteReadAgingCommandFactory()
    };
    CommandInfo CMD_4_ERASE_AND_WRITE_AGING_INFO = {
        CMD_4_ERASE_AND_WRITE_AGING,
        CMD_4_ERASE_AND_WRITE_AGING_HELP,
        new EraseAndWriteAgingCommandFactory()
    };
    CommandInfo CMD_ERASE_INFO = { CMD_ERASE, CMD_ERASE_HELP, new EraseCommandFactory() };
    CommandInfo CMD_ERASE_RANGE_INFO = { CMD_ERASE_RANGE, CMD_ERASE_RANGE_HELP, new EraseRangeCommandFactory() };
}

const std::map<std::string, CommandInfo> cmdList = {
    {CMD_HELP, CMD_HELP_INFO},
    {CMD_READ, CMD_READ_INFO},
    {CMD_WRITE, CMD_WRITE_INFO},
    {CMD_EXIT, CMD_EXIT_INFO},
    {CMD_FULLWRITE, CMD_FULLWRITE_INFO},
    {CMD_FULLREAD, CMD_FULLREAD_INFO},
    {CMD_FLUSH, CMD_FLUSH_INFO},
    {CMD_1_FULL_WRITE_AND_READ_COMPARE, CMD_1_FULL_WRITE_AND_READ_COMPARE_INFO},
    {CMD_2_PARTIAL_LBA_WRITE, CMD_2_PARTIAL_LBA_WRITE_INFO},
    {CMD_3_WRITE_READ_AGING, CMD_3_WRITE_READ_AGING_INFO},
    {CMD_4_ERASE_AND_WRITE_AGING, CMD_4_ERASE_AND_WRITE_AGING_INFO},
    {CMD_ERASE, CMD_ERASE_INFO},
    {CMD_ERASE_RANGE, CMD_ERASE_RANGE_INFO}
};
