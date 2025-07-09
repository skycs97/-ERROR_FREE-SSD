#ifdef _DEBUG
#include "gmock/gmock.h"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
#include "shell.h"
#include "ssd_impl.h"

int main(int argc, char* argv[]) {
	SsdImpl ssd;
	TestShell& shell = TestShell::getShell();
	shell.runner.setStorage(&ssd);
	shell.runShell(argc, argv);
}

#endif

