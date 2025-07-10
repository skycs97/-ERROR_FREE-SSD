#pragma once

// SSD
#define MAX_LBA 99
#define MIN_LBA 0
#define CMD_INVALID	0xFFFF
#define CMD_READ	1
#define CMD_WRITE	2
#define CMD_ERASE	3
#define CMD_FLUSH	4
#define INVALID_VALUE	0xFFFF

// NAND
#define NAND_DATA_EMPTY	"0x00000000"

// ArgumentParser
#define ARG_IDX_CMD		1
#define ARG_IDX_ADDR	2
#define ARG_IDX_ERASE_START_ADDR 2
#define ARG_IDX_DATA	3
#define ARG_IDX_ERASE_COUNT 3
#define MIN_ARG_CNT     2
#define READ_CORRECT_ARG_SIZE	3
#define WRITE_CORRECT_ARG_SIZE	4
#define ERASE_CORRECT_ARG_SIZE	4
#define FLUSH_CORRECT_ARG_SIZE	2

// File
#define NAND_FILENAME	"ssd_nand.txt"
#define OUTPUT_FILENAME "ssd_output.txt"

// Buffer
#define BUFFER_ENABLE true
#define BUFFER_DIR_NAME	"buffer"
#define BUFFER_SIZE 5
#define BUFFER_NAME_EMPTY	"empty"

typedef int CMD_TYPE;