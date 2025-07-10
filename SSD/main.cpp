#ifdef _DEBUG
#include "gmock/gmock.h"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
#include "ssd.h"

int main(int argc, const char* argv[]) {
	SSD* ssd = SSD::getInstance();
	ssd->run(argc, argv);
}
#endif