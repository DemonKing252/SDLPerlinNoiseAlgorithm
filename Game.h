#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <list>
#include <ctime>
#include <vector>
#define ROWS 768
#define COLS 768
using namespace std;


class PerlinNoiseApp
{
protected:
	bool m_bRunning;
	SDL_Renderer* m_pRenderer;
	SDL_Window* m_pWindow;
public:
	int nOutputWidth;
	int nOutputHeight;
	float *fNoiseSeed2D = nullptr;
	float *fPerlinNoise2D = nullptr;

	TTF_Font* calibriRegular;

	static PerlinNoiseApp* Instance()
	{
		static PerlinNoiseApp* instance = new PerlinNoiseApp();
		return instance;
	}

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool running();
	void handleEvents();
	SDL_Renderer* getRenderer() { return m_pRenderer; }
	void update();
	void render();
	void clean();

};
