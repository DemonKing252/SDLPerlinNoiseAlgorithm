#include "Game.h"
void PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput)
{
	for (int x = 0; x < nWidth; x++)
	for (int y = 0; y < nHeight; y++)
	{
		float fNoise = 0.0f;
		float fScaleAcc = 0.0f;
		float fScale = 1.0f;

		for (int o = 0; o < nOctaves; o++)
		{
			int nPitch = nWidth >> o;
			int nSampleX1 = (x / nPitch) * nPitch;
			int nSampleY1 = (y / nPitch) * nPitch;

			int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
			int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

			float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
			float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

			float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
			float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

			fScaleAcc += fScale;
			fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
			fScale = fScale / fBias;
		}

		// Scale to seed range
		fOutput[y * nWidth + x] = fNoise / fScaleAcc;
	}
}

bool PerlinNoiseApp::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "SDL Init successful" << endl;
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0)
		{
			cout << "Window creation successful" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
		else
		{
			cout << "Window Init fail" << endl;
			return false;
		}
		if (IMG_Init(IMG_INIT_PNG))
		{
			cout << "image init success" << endl;
		}
		else
		{
			cout << "png image init fail" << endl;
			return false; // Window init fail.
		}
		if (Mix_Init(MIX_INIT_MP3) != 0) // Mixer init success.
		{
			Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 8192);
			Mix_AllocateChannels(16);
		}
		else
		{
			cout << "audio init fail" << endl;
			return false; // Window init fail.
		}
		if (TTF_Init() == 0)
		{

		}
		else
		{
			cout << "ttf init fail" << endl;
			return false; // Window init fail.
		}
	}
	else
	{
		cout << "SDL Init fail" << endl;
		return false;
	}
	srand((unsigned)time(NULL));

	cout << "Init success" << endl;
	m_bRunning = true;	//	Initialize the engine
	//Initialize the texture
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

	calibriRegular = TTF_OpenFont("Assets/calibri.ttf", 9);
	
	// start

	// 2D noise variables
	
	nOutputWidth = ROWS;
	nOutputHeight = COLS;

	int nOctaveCount = 5;
	float fScalingBias = 2.0f;
	int nMode = 1;

	fNoiseSeed2D = new float[nOutputWidth * nOutputHeight];
	fPerlinNoise2D = new float[nOutputWidth * nOutputHeight];


	for (int i = 0; i < nOutputWidth * nOutputHeight; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;


	PerlinNoise2D(nOutputWidth, nOutputHeight, fNoiseSeed2D, nOctaveCount, fScalingBias, fPerlinNoise2D);



	return true;
}

bool PerlinNoiseApp::running()
{
	return m_bRunning;
}

void PerlinNoiseApp::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		}
	}
}

void PerlinNoiseApp::update()
{
}

void PerlinNoiseApp::render()
{
	for (int x = 0; x < ROWS; x++)
	{
		for (int y = 0; y < COLS; y++)
		{
			int pixel_bw = (float)(fPerlinNoise2D[y * ROWS + x] * 12.0f);

			SDL_SetRenderDrawColor(PerlinNoiseApp::Instance()->getRenderer(), 12,
									            (Uint8)(pixel_bw * 35),
									 							   12,
									 							  255);
			SDL_RenderDrawPoint(m_pRenderer, x, y);
		}
	}

	SDL_RenderPresent(m_pRenderer);
	SDL_RenderClear(m_pRenderer);
}

void PerlinNoiseApp::clean()
{
	SDL_Quit();
}

