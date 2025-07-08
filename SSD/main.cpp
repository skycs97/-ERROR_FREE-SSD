#ifdef _DEBUG
#include "gmock/gmock.h"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
#include "ssd.h"

int main(int argc, char* argv[]) {
	// 1. Create SSD instance
	SSD& ssd = SSD::getInstance();
	
	// 2. Parsing command

	// 3. Process command
	ssd.run();
}
#endif