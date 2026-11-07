#include <string>
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

TEST(Viewer_MouseCaptureRefreshesWhenSdlStateIsStale)
{
	// Wanted and SDL already agrees: leave it alone unless a refresh event arrived.
	CHECK(!mouseCaptureNeedsRelease(true, true, true, false));
	CHECK(!mouseCaptureNeedsAcquire(true, true, true));
	// Focus/fullscreen events cycle capture even though SDL still reports it on.
	CHECK(mouseCaptureNeedsRelease(true, true, true, true));
	CHECK(mouseCaptureNeedsAcquire(true, false, false));
	// Not wanted: release whatever is on; nothing to release when already off.
	CHECK(mouseCaptureNeedsRelease(false, true, false, false));
	CHECK(mouseCaptureNeedsRelease(false, false, true, false));
	CHECK(!mouseCaptureNeedsRelease(false, false, false, true));
	CHECK(!mouseCaptureNeedsAcquire(false, false, false));
	// Half-applied state (relative on, grab off) is completed.
	CHECK(mouseCaptureNeedsAcquire(true, true, false));
}

TEST(Viewer_MouseCaptureBlockerNamesTheFlag)
{
	CHECK(std::string(mouseCaptureBlocker(true, false, false, true)) == "none");
	CHECK(std::string(mouseCaptureBlocker(false, false, false, true)) == "not-playing");
	CHECK(std::string(mouseCaptureBlocker(true, true, true, false)) == "pointer");
	CHECK(std::string(mouseCaptureBlocker(true, false, true, false)) == "menu");
	CHECK(std::string(mouseCaptureBlocker(true, false, false, false)) == "unfocused");
}
