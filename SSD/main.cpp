#ifdef _DEBUG
#include "gmock/gmock.h"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
#include "ssd.h"

int main(int argc, const char* argv[]) {
	FileHandler* fileHandler = new FileHandler();
	SSD* ssd = new SSD(fileHandler);
	ssd->run(argc, argv);
}
#endif