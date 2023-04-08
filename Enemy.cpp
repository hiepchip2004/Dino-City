#include "Enemy.h"

Enemy::Enemy(int _type)
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
	if (type == FlyingEnemy)
	{
		posX = rand() % (sWidth + EnemyPositionRange) + sWidth;
		posY = rand() % (EnemyMaxHeight - EnemyMinHeight + 1) + EnemyMinHeight;
	}
	else if (type == StandingEnemy)
	{
		posX = rand() % (sWidth + EnemyPositionRange) + sWidth;
		posY = Ground - 8;
	}

	EnemyTexture = nullptr;
}

Enemy::~Enemy()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = 0;
	if (EnemyTexture != nullptr)
	{
		EnemyTexture = nullptr;
	}
}

void Enemy::LoadFromFile(string path, SDL_Renderer* gRenderer)
{
	SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		LogError("Can not load image.", ImgError);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			LogError("Can not create texture from surface.", SDL_ERROR);
		}
		else
		{
			eWidth = tmpSurface->w;
			eHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	EnemyTexture = tmpTexture;
}

void Enemy::Move(const int &acceleration)
{
	posX += -(EnemySpeed + acceleration);
	if (posX + MaxEnemyWidth< 0)
	{
		posX = rand() % (sWidth + EnemyPositionRange) + sWidth;

		if (type == FlyingEnemy)
		{
			posY = rand() % (EnemyMaxHeight- EnemyMinHeight+ 1) + EnemyMinHeight;
		}
	}
}

void Enemy::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, EnemyTexture, currentClip, &renderSpace);
}

int Enemy::GetType()
{
	if (type == FlyingEnemy)
	{
		return FlyingEnemy;
	}
	else
	{
		return StandingEnemy;
	}
}

int Enemy::GetSpeed(const int &acceleration)
{
	return EnemySpeed + acceleration;
}

int Enemy::GetPosX()
{
	return posX;
}

int Enemy::GetPosY()
{
	return posY;
}

int Enemy::GetWidth()
{
	return eWidth;
}

int Enemy::GetHeight()
{
	return eHeight;
}