#include "Main/MouseCapture.h"
#include "TestMain.h"

using namespace dice::hfe;

TEST(Viewer_MouseCaptureFollowsFocusAndMenuOwnership)
{
	// A gameplay window opened without focus acquires capture when focused.
	CHECK(!gameplayMouseCaptureWanted(true, false, false, false));
	CHECK(gameplayMouseCaptureWanted(true, false, false, true));

	// Focus loss and pointer/menu ownership release it; returning to focused
	// gameplay reacquires it without requiring another pointer transition.
	CHECK(!gameplayMouseCaptureWanted(true, false, false, false));
	CHECK(!gameplayMouseCaptureWanted(true, true, false, true));
	CHECK(!gameplayMouseCaptureWanted(true, false, true, true));
	CHECK(gameplayMouseCaptureWanted(true, false, false, true));
	CHECK(!gameplayMouseCaptureWanted(false, false, false, true));
}
