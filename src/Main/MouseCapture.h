// The native viewer captures only while gameplay owns an active, focused
// window. Kept independent of SDL so the lifecycle policy can be regression
// tested without opening a window.
#pragma once

namespace dice::hfe {

constexpr bool gameplayMouseCaptureWanted(bool playing, bool pointer, bool menuUp, bool focused)
{
	return playing && !pointer && !menuUp && focused;
}

} // namespace dice::hfe
