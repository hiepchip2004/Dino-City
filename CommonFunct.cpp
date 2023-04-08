#include "CommonFunct.h"

void LogError(string msg, int error_code)
{
	if (error_code == SDL_ERROR)
	{
		cout << msg << SDL_GetError() << endl;
	}
	if (error_code == ImgError)
	{
		cout << msg << IMG_GetError() << endl;
	}
	if (error_code == MixError)
	{
		cout << msg << Mix_GetError() << endl;
	}
	if (error_code == TtfError)
	{
		cout << msg << TTF_GetError() << endl;
	}
}