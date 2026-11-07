// The native viewer captures only while gameplay owns an active, focused
// window. Kept independent of SDL so the lifecycle policy can be regression
// tested without opening a window.
#pragma once

namespace dice::hfe {

constexpr bool gameplayMouseCaptureWanted(bool playing, bool pointer, bool menuUp, bool focused)
{
	return playing && !pointer && !menuUp && focused;
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

// The soldier's aim pitch is clamped (85 degrees first person), but a driver's
// PIPitch/PIMouseLookY is the per-tick change of that pitch, so a clamp pinned
// at one end swallows the mouse in that direction. Driving only bounds the sum.
constexpr float clampLookPitch(float pitch, bool firstPerson, bool driving)
{
	const float low = driving ? -1000.0f : firstPerson ? -1.4835f : -1.2f;
	const float high = driving ? 1000.0f : firstPerson ? 1.4835f : 1.0f;
	return pitch < low ? low : pitch > high ? high : pitch;
}

} // namespace dice::hfe
