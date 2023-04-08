#pragma once

#include "LTexture.h"

#define JUMP 1
#define FALL 2
#define RUN	0

class Character
{
public:
	static const int JumpSpeed = 7;
	static const int FallSpeed = 7;

	Character();

	bool OnGround();

	void HandleEvent(SDL_Event& e, Mix_Chunk *gJump);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

private:
	int posX, posY;

	int status;

	int jumpStart;

	bool isFalling;
};

