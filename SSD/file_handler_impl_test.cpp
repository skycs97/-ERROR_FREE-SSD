#include "gmock/gmock.h"
#include "file_handler_impl.h"

TEST(FileHandlerImpl, DISABLED_rename) {
	FileHandlerImpl fileHandler;
	EXPECT_NO_THROW(fileHandler.rename("aaa.txt", "bbb.txt"));
}