#pragma once
#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

class Sprite
{
	public:
		Sprite(void);
		Sprite(std::string file);
		~Sprite(void);
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render(int x, int y);
		int GetWidth(void);
		int GetHeight(void);
		bool IsOpen(void);
	private:
        SDL_Texture *texture = nullptr;
		int width;
		int height;
		SDL_Rect clipRect;

		SDL_Rect dstRect;
};

