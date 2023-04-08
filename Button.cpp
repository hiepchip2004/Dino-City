#include "Button.h"

Button::Button()
{
	pos.x = 0;
	pos.y = 0;

	currentSprite = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y)
{
	pos.x = x;
	pos.y = y;

	currentSprite = BUTTON_MOUSE_OUT;
}

void Button::SetPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

bool Button::IsInside(SDL_Event *e, int size)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int button_width, button_height;
		if (size == SmallButton)
		{
			button_width = SmallButWidth;
			button_height = SmallButHeight;
		}
		else
		{
			button_width = CommonButWidth;
			button_height = CommonButHeight;
		}

		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < pos.x)
		{
			inside = false;
		}
		else if (x > pos.x + button_width)
		{
			inside = false;
		}
		else if (y < pos.y)
		{
			inside = false;
		}
		else if (y > pos.y + button_height)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture)
{
	gButtonTexture.Render(pos.x, pos.y, gRenderer, currentClip);
}