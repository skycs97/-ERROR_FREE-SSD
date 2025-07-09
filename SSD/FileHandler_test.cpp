#include "gmock/gmock.h"
#include "FileHandler.h"
TEST(FileHandler, DISABLED_rename) {
	FileHandler fileHandler;
	EXPECT_NO_THROW(fileHandler.rename("aaa.txt", "bbb.txt"));
}