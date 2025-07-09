#pragma once

// SSD
#define MAX_LBA 99
#define MIN_LBA 0

// ArgumentParser
#define ARG_IDX_CMD		1
#define ARG_IDX_ADDR	2
#define ARG_IDX_DATA	3
#define MIN_ARG_CNT     2
#define READ_CORRECT_ARG_SIZE	3
#define WRITE_CORRECT_ARG_SIZE	4
#define ERASE_CORRECT_ARG_SIZE	4

// File
#define NAND_FILENAME	"ssd_nand.txt"
#define OUTPUT_FILENAME "ssd_output.txt"

// Buffer
#define BUFFER_ENABLE false
#define BUFFER_DIR_NAME	"buffer"
#define BUFFER_SIZE 5
#define PREFIX_BUFFER_FILE1	"1_"
#define PREFIX_BUFFER_FILE2	"2_"
#define PREFIX_BUFFER_FILE3	"3_"
#define PREFIX_BUFFER_FILE4	"4_"
#define PREFIX_BUFFER_FILE5	"5_"
#define BUFFER_NAME_EMPTY	"empty"