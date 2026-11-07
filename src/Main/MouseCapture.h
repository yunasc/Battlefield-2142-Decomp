// The native viewer captures only while gameplay owns an active, focused
// window. Kept independent of SDL so the lifecycle policy can be regression
// tested without opening a window.
#pragma once

namespace dice::hfe {

constexpr bool gameplayMouseCaptureWanted(bool playing, bool pointer, bool menuUp, bool focused)
{
	return playing && !pointer && !menuUp && focused;
}

// Why capture is not wanted, for the always-on log line ("none" when it is).
constexpr const char* mouseCaptureBlocker(bool playing, bool pointer, bool menuUp, bool focused)
{
	return !playing ? "not-playing" : pointer ? "pointer" : menuUp ? "menu" : !focused ? "unfocused" : "none";
}

// SDL reports its own flags, which can stay set while the OS-level capture was
// dropped (focus return, fullscreen/Space change, a click after Mission Control).
// A refresh event therefore releases and re-takes capture even when SDL agrees.
constexpr bool mouseCaptureNeedsRelease(bool wanted, bool relative, bool grabbed, bool refresh)
{
	return (relative || grabbed) && (!wanted || refresh);
}

constexpr bool mouseCaptureNeedsAcquire(bool wanted, bool relative, bool grabbed)
{
	return wanted && (!relative || !grabbed);
}

} // namespace dice::hfe
