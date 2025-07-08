#ifdef _DEBUG
#include "gmock/gmock.h"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
#include "shell.h"

int main(void) {
	TestShell& shell = TestShell::getShell();
	shell.runShell();
}

#endif

