#include "CommonFunct.h"
#include "Utils.h"
#include "LTexture.h"
#include "Button.h"
#include "Character.h"
#include "Enemy.h"

const string LAYER[BackgroundLayer] = {
	"imgs/background/1.png", 
	"imgs/background/2.png",
	"imgs/background/3.png",
	"imgs/background/4.png",
	"imgs/background/5.png",
};

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[DinoFrames];
SDL_Rect gEnemyClips[BirdFrames];

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture[BackgroundLayer];
LTexture gCharacterTexture;
LTexture gGroundTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gLoseTexture;
LTexture gText1Texture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;

Button PlayButton(PlayButX, PlayButY);
Button HelpButton(HelpButX, HelpButY);
Button BackButton(BackButX, BackButY);
Button PauseButton(PauseButX, PauseButY);
Button ContinueButton(ContinueButX, ContinueButY);

Character character;

int main(int argc, char* args[])
{
	if (!Init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		if (!LoadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			bool Quit_Menu = false;
			bool Play_Again = false;

			Mix_PlayMusic(gMenuMusic, Repeatable);
			while (!Quit_Menu)
			{
				SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}

					bool Quit_Game = false;
					HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);
						
					HandleHelpButton(&e_mouse, gBackButton,
									 HelpButton, BackButton, 
									 gInstructionTexture, gBackButtonTexture,
									 gRenderer, Quit_Game, gClick);

					if (Quit_Game == true)
					{
						return 0;
					}
				}

				gMenuTexture.Render(0, 0, gRenderer);

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

				SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
				HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

				SDL_RenderPresent(gRenderer);
			}

			while (Play_Again)
			{
				srand(time(NULL));
				int time = 0;
				int score = 0;
				int acceleration = 0;
				int frame_Character = 0;
				int frame_Enemy = 0;
				string highscore = GetHighScoreFromFile("high_score.txt");
				
				SDL_Event e;
				Enemy sign(StandingEnemy);
				Enemy rock(StandingEnemy);
				Enemy bird(FlyingEnemy);
				
				Mix_PlayMusic(gMusic, Repeatable);
				GenerateEnemy(sign, rock, bird, gEnemyClips, gRenderer);

				int OffsetSpeed_Ground = BaseOffsetSpeed;
				vector <double> OffsetSpeed_Bkgr(BackgroundLayer, BaseOffsetSpeed);				

				bool Quit = false;
				bool Game_State = true;
				while (!Quit)
				{
					if (Game_State)
					{
						UpdateGameTimeAndScore(time, acceleration, score);

						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								Quit = true;
								Play_Again = false;
							}

							HandlePauseButton(&e, gRenderer, gContinueButton,
								PauseButton, ContinueButton,
								gContinueButtonTexture, Game_State, gClick);

							character.HandleEvent(e, gJump);
						}
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);

						//cuộn nền
						RenderScrollingBackground(OffsetSpeed_Bkgr, gBackgroundTexture, gRenderer);
						//cuộn đường đi
						RenderScrollingGround(OffsetSpeed_Ground, acceleration, gGroundTexture, gRenderer);

						character.Move();
						SDL_Rect* currentClip_Character = nullptr;
						if (character.OnGround())
						{
							currentClip_Character = &gCharacterClips[frame_Character / 7];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}
						else
						{
							currentClip_Character = &gCharacterClips[0];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}

						sign.Move(acceleration);
						sign.Render(gRenderer);
			
						rock.Move(acceleration);
						rock.Render(gRenderer);

						SDL_Rect* currentClip_Enemy = &gEnemyClips[frame_Enemy / SlowFrameEnemy];
						bird.Move(acceleration);
						bird.Render(gRenderer, currentClip_Enemy);


						SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
						PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);


						DrawPlayerScore(gText1Texture, gScoreTexture, textColor, gRenderer, gFont, score);
						DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);

						if (CheckEnemyColission(character,
							sign, rock, bird,
							currentClip_Character, currentClip_Enemy))
						{
							Mix_PauseMusic();
							Mix_PlayChannel(MixChannel, gLose, NotRepeatable);
							UpdateHighScore("high_score.txt", score, highscore);
							Quit = true;
						}


						SDL_RenderPresent(gRenderer);

						ControlCharFrame(frame_Character);
						ControlEnemyFrame(frame_Enemy);
					}
				}

				DrawEndGameSelection(gLoseTexture, &e, gRenderer, Play_Again);
				if (!Play_Again)
				{
					sign.~Enemy();
					rock.~Enemy();
					bird.~Enemy();
				}
			}
		}
	}
	Close();

	return 0;
}


bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(wTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   sWidth, sHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", ImgError);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
					success = false;
				}

				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

	gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load background music", MixError);
		success = false;
	}

	gMenuMusic = Mix_LoadMUS("sound/do_toc 2.wav");
	if (gMenuMusic == nullptr)
	{
		LogError("Failed to load menu music", MixError);
		success = false;
	}

	gClick = Mix_LoadWAV("sound/mouse_click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MixError);
		success = false;
	}

	gJump = Mix_LoadWAV("sound/jump.wav");
	if (gJump == nullptr)
	{
		LogError("Failed to load jumping sound", MixError);
		success = false;
	}

	gLose = Mix_LoadWAV("sound/lose_sound.wav");
	if (gLose == nullptr)
	{
		LogError("Failed to load lose sound", MixError);
		success = false;
	}

	else
	{
		gFont = TTF_OpenFont("font/valorax_font.ttf", 28);
		if (gFont == NULL)
		{
			LogError("Failed to load font", MixError);
			success = false;
		}
		else
		{
			if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer))
			{
				cout << "Failed to render text1 texture" << endl;
				success = false;
			}

			if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer))
			{
				cout << "Failed to render text2 texture" << endl;
				success = false;
			}
			
			if (!gMenuTexture.LoadFromFile("imgs/background/menu.png", gRenderer))
			{
				cout << "Failed to load menu image" << endl;
				success = false;
			}

			if (!gInstructionTexture.LoadFromFile("imgs/background/intro.png", gRenderer))
			{
				cout << "Failed to load intro image" << endl;
				success = false;
			}
			if (!gLoseTexture.LoadFromFile("imgs/background/lose1.png", gRenderer))
			{
				cout << "Failed to load lose image" << endl;
				success = false;
			}

			if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", gRenderer))
			{
				cout << "Failed to load play_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPlayButton[i] = { 250 * i, 0, 250, 70 };
				}
			}

			if (!gHelpButtonTexture.LoadFromFile("imgs/button/big_button/intro_button.png", gRenderer))
			{
				cout << "Failed to load intro_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHelpButton[i] = { 250 * i, 0, 250, 70 };
				}
			}

			if (!gBackButtonTexture.LoadFromFile("imgs/button/big_button/back_but.png", gRenderer))
			{
				cout << "Failed to load back_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i] = { 96 * i, 0, 96, 70 };
				}
			}

			if (!gPauseButtonTexture.LoadFromFile("imgs/button/big_button/pause_but.png", gRenderer))
			{
				cout << "Failed to load pause_button image " << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPauseButton[i] = { 47 * i, 0, 47, 34 };
				} 
			}

			if (!gContinueButtonTexture.LoadFromFile("imgs/button/big_button/continue_but.png", gRenderer))
			{
				cout << "Failed to load continue_button image " << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gContinueButton[i] = { 47 * i, 0, 47, 34 };
				}
			}
			

			for (int i = 0; i < BackgroundLayer; ++i)
			{
				if (!gBackgroundTexture[i].LoadFromFile(LAYER[i].c_str(), gRenderer))
				{
					cout << "Failed to load background image" << endl;
					success = false;
				}
			}

			if (!gCharacterTexture.LoadFromFile("imgs/character/move.png", gRenderer))
			{
				cout << "Failed to load character_run image." << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < DinoFrames; i++) {
					gCharacterClips[i] = { 60 * i , 0 , 60 , 60 };
				}
			}
		}
	}
	return success;
}

void Close()
{
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gCharacterTexture.Free();
	gGroundTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	gLoseTexture.Free();
	gText1Texture.Free();
	gScoreTexture.Free();
	gText2Texture.Free();
	gHighScoreTexture.Free();

	for (int i = 0; i < BackgroundLayer; ++i)
	{
		gBackgroundTexture[i].Free();
	}

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}
