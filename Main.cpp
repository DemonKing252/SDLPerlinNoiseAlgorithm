#include "Game.h"
#include <iostream>
#include "SDL.h"
#include "Game.h"
#define FPS 60
using namespace std;
int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime, delayTime = 1000.0f / FPS;
	PerlinNoiseApp::Instance()->init("Perlin Noise Algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 768, SDL_WINDOW_RESIZABLE);
	while (PerlinNoiseApp::Instance()->running())
	{
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < delayTime)
		{
			SDL_Delay((int)delayTime - frameTime);
		}
		PerlinNoiseApp::Instance()->handleEvents();
		PerlinNoiseApp::Instance()->update();
		PerlinNoiseApp::Instance()->render();
	}
	PerlinNoiseApp::Instance()->clean();
	return 0;
}