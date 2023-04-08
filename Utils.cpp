#include "Utils.h"

string GetHighScoreFromFile(string path)
{
	fstream HighScoreFile;
	string highscore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(string path,
	const int& score,
	const string& old_high_score)
{
	int oldHighScore = 0;
	fstream HighScoreFile;
	string newHighScore;
	stringstream ConvertToInt(old_high_score);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = to_string(oldHighScore);

	HighScoreFile.open(path, std::ios::out);
	HighScoreFile << newHighScore;
	HighScoreFile.close();
}
int UpdateGameTimeAndScore(int& time,
	int& speed,
	int& score)
{
	if (time == TimeMax)
	{
		speed += SpeedIncreasing;
	}

	if (time > TimeMax)
	{
		time = 0;
	}
	if (time % 5 == 0)
	{
		score += ScoreIncreasing;
	}
	
	time += TimeIncreasing;

	return time;
}

void RenderScrollingBackground(vector <double>& offsetSpeed,
	LTexture(&gBackgroundTexture)[BackgroundLayer],
	SDL_Renderer* gRenderer)
{
	vector <double> layer_speed;
	layer_speed.push_back(Layer1Speed);
	layer_speed.push_back(Layer2Speed);
	layer_speed.push_back(Layer3Speed);
	layer_speed.push_back(Layer4Speed);
	layer_speed.push_back(Layer5Speed);

	for (int i = 0; i < BackgroundLayer; ++i)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -gBackgroundTexture[i].GetWidth())
		{
			offsetSpeed[i] = 0;
		}
		gBackgroundTexture[i].Render(offsetSpeed[i], 0, gRenderer);
		gBackgroundTexture[i].Render(offsetSpeed[i] + gBackgroundTexture[i].GetWidth(), 0, gRenderer);
	}
}

void RenderScrollingGround(int& speed,
	const int acceleration,
	LTexture gGroundTexture,
	SDL_Renderer* gRenderer)
{
	speed -= GroundSpeed + acceleration;
	if (speed < -gGroundTexture.GetWidth())
	{
		speed = 0;
	}
	gGroundTexture.Render(speed, 0, gRenderer);
	gGroundTexture.Render(speed + gGroundTexture.GetWidth(), 0, gRenderer);
}

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e, CommonButton))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MixChannel, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton, 
	Button& BackButton, 
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture, 
	SDL_Renderer *gRenderer, 
	bool &Quit_game, 
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(e, CommonButton))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MixChannel, gClick, NotRepeatable);

			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_game = true;
						Close();
					}

					else if (BackButton.IsInside(e, CommonButton))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MixChannel, gClick, NotRepeatable);
							ReadDone = true;
							break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				} while (SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, CommonButton))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MixChannel, gClick, NotRepeatable);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleContinueButton(Button ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State,
	Mix_Chunk* gClick)
{
	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (ContinueButton.IsInside(e, SmallButton))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
					Mix_PlayChannel(MixChannel, gClick, NotRepeatable);
					Mix_ResumeMusic();
					Game_State = true;
					Back_To_Game = true;
				}
				break;
				}
			}
			else
			{
				ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			}
		
			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite];
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}

void HandlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer, 
	SDL_Rect (&gContinueButton)[BUTTON_TOTAL], 
	Button& PauseButton, 
	Button ContinueButton, 
	LTexture gContinueButtonTexture, 
	bool &Game_State, 
	Mix_Chunk *gClick)
{
	if (PauseButton.IsInside(e, SmallButton))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MixChannel, gClick, NotRepeatable);
			Mix_PauseMusic();
			break;
		case SDL_MOUSEBUTTONUP:
			Game_State = false;
			HandleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State, gClick);
			break;
		}
	}
	else
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void GenerateEnemy(Enemy& sign,
	Enemy& rock,
	Enemy& bird,
	SDL_Rect(&gEnemyClips)[BirdFrames], 
	SDL_Renderer * gRenderer)
{
	sign.LoadFromFile("imgs/enemy/stop_img.png", gRenderer);
	rock.LoadFromFile("imgs/enemy/rock.png", gRenderer);
	bird.LoadFromFile("imgs/enemy/bird.png", gRenderer);
	{
		gEnemyClips[0] = { 45 * 7, 0, 45, 40 };
		gEnemyClips[1] = { 45 * 6, 0, 45, 40 };
		gEnemyClips[2] = { 45 * 5, 0, 45, 40 };
		gEnemyClips[3] = { 45 * 4, 0, 45, 40 };
		gEnemyClips[4] = { 45 * 3, 0, 45, 40 };
		gEnemyClips[5] = { 45 * 2, 0, 45, 40 };
		gEnemyClips[6] = { 45 * 1, 0, 45, 40 };
		gEnemyClips[7] = { 45 * 0, 0, 45, 40 };
	}
}

bool CheckColission(Character character,
	SDL_Rect* char_clip,
	Enemy enemy, 
	SDL_Rect* enemy_clip)
{
	bool collide = false;
	
	int left_a = character.GetPosX();
	int right_a = character.GetPosX() + char_clip->w;
	int top_a = character.GetPosY();
	int bottom_a = character.GetPosY() + char_clip->h;

	if (enemy.GetType() == StandingEnemy)
	{
		const int TRASH_PIXEL_1 = 25;
		const int TRASH_PIXEL_2 = 30;

		int left_b = enemy.GetPosX();
		int right_b = enemy.GetPosX() + enemy.GetWidth();
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy.GetHeight();

		if (right_a - TRASH_PIXEL_1 >= left_b && left_a + TRASH_PIXEL_1 <= right_b)
		{
			if (bottom_a - TRASH_PIXEL_2 >= top_b)
			{
				collide = true;
			}
		}
	}
	else
	{
		const int TRASH_PIXEL_1 = 22;
		const int TRASH_PIXEL_2 = 18;

		int left_b = enemy.GetPosX() + TRASH_PIXEL_1;
		int right_b = enemy.GetPosX() + enemy_clip->w - TRASH_PIXEL_1;
		int top_b = enemy.GetPosY();
		int bottom_b = enemy.GetPosY() + enemy_clip->h - TRASH_PIXEL_2;

		if (right_a >= left_b && left_a <= right_b)
		{
			if (top_a <= bottom_b && top_a >= top_b)
			{
				collide = true;
			}
			
			if (bottom_a >= bottom_b && bottom_a <= top_b)
			{
				collide = true;
			}
		}
	}

	return collide;
}

bool CheckEnemyColission(Character character,
	Enemy sign,
	Enemy rock, 
	Enemy bird,
	SDL_Rect* char_clip,
	SDL_Rect* enemy_clip
	)
{
	if (CheckColission(character, char_clip, sign))
	{
		return true;
	}
	if (CheckColission(character, char_clip, rock))
	{
		return true;
	}
	if (CheckColission(character, char_clip, bird, enemy_clip))
	{
		return true;
	 }
	return false;
}

void ControlCharFrame(int &frame)
{
	frame += FrameIncreasing;
	if (frame / SlowFrameChar >= DinoFrames)
	{
		frame = 0;
	}
}

void ControlEnemyFrame(int &frame)
{
	frame += FrameIncreasing;
	if (frame / SlowFrameEnemy >= BirdFrames)
	{
		frame = 0;
	}
}

void DrawPlayerScore(LTexture gTextTexture,
	LTexture gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *gRenderer,
	TTF_Font *gFont, 
	const int& score)
{
	gTextTexture.Render(Text1X, Text1Y, gRenderer);
	if (gScoreTexture.LoadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.Render(ScoreX, ScoreY, gRenderer);
	}
}

void DrawPlayerHighScore(LTexture gTextTexture,
	LTexture gHighScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const std::string& HighScore)
{
	gTextTexture.Render(Text2X, Text2Y, gRenderer);
	if (gHighScoreTexture.LoadFromRenderedText(HighScore, gFont, textColor, gRenderer))
	{
		gHighScoreTexture.Render(HighScoreX, HighScoreY, gRenderer);
	}
}

void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event *e, 
	SDL_Renderer *gRenderer,
	bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					}
				}
			}

			gLoseTexture.Render(0, 0, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
}
