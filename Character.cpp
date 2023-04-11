#include "Character.h"

//vị  trí của nhân vật  
Character::Character()
{
	posX = sWidth - 700;
	posY = Ground;

	status = 0;
}

//check đường đi
bool Character::OnGround()
{
	return posY == Ground;
}

//xử lí bàn phím 
void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (OnGround())
				{
					Mix_PlayChannel(MixChannel, gJump, NotRepeatable);
					status = JUMP;
					jumpStart = SDL_GetTicks();
				}
			}
			case SDLK_SPACE:
				if (OnGround())
				{
					Mix_PlayChannel(MixChannel, gJump, NotRepeatable);
					status = JUMP;
					jumpStart = SDL_GetTicks();
				}
		}
	}
}

//nhảy 
void Character::Move()
{
	if (status == JUMP && posY >= MaxHeight)
	{
		posY -= JumpSpeed;
		Uint32 jumpTime = SDL_GetTicks() - jumpStart;
		if (jumpTime > 350) {
			isFalling = true;
			status = FALL;
		}
	}
	if (isFalling || posY < Ground && SDL_GetTicks() - jumpStart > 250) {
		posY += FallSpeed;
		if (posY >= Ground) { // gặp ground ngừng rơi 
			posY = Ground;
			isFalling = false;
			status = RUN;
		}
	}
}


void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}
