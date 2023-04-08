#pragma once

#include "CommonFunct.h"

class LTexture
{
public:
	LTexture();

	~LTexture();

	void Free();

	bool LoadFromRenderedText(string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	bool LoadFromFile(string path, SDL_Renderer *gRenderer);

	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

	int GetWidth();

	int GetHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

