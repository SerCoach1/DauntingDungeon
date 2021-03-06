#pragma once
#include "SDL2/SDL.h"

class FPSCounter {
public:
	FPSCounter();
	void Init();
	void Limit();
	void Count();
	void FrameStart();
	int GetFPS();
	void FrameEnd();
	Uint32 GetDeltaTime();

private:
	Uint32 frameStart, frameTime, secondStart, frameEnd;
	const int FPS = 60;
	const Uint32 FRAME_DELAY = 1000 / FPS;
	int frames;
	int fps;
};