#ifdef _DEBUG
#include "gmock/gmock.h"

int main(void) {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else

int main(void) {

}

#endif

