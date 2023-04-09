#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

const int SDL_ERROR = 1;
#define ImgError 2
#define MixError 3
#define TtfError 4

#define MixChannel -1

#define TimeMax 1000
#define Ground 470
#define MaxHeight 250

#define BaseOffsetSpeed 0

#define SpeedIncreasing 2
#define ScoreIncreasing 1
#define TimeIncreasing 1
#define FrameIncreasing 1

#define GroundSpeed 3
#define EnemySpeed 3
#define MaxEnemyWidth 100

#define FlyingEnemy 1
#define StandingEnemy 0

#define SlowFrameChar 4
#define SlowFrameEnemy 4

#define Repeatable -1
#define NotRepeatable 0

#define SmallButton 1
#define CommonButton 2
#define EnemyMaxHeight 230
#define EnemyMinHeight 330

#define EnemyPositionRange 250
#define StopSignRange 100
#define CarRange 350
#define BirdRange 500

const string wTitle = "Dino City";

const int sWidth = 928;
const int sHeight = 522;

const int CommonButWidth = 250;
const int CommonButHeight = 70;
const int SmallButWidth = 47;
const int SmallButHeight = 34;

const int PlayButX = 339;
const int PlayButY= 100;
const int IntroButX= 339;
const int IntroButY = 200;
const int BackButX = 31;
const int BackButY = 29;
const int PauseButX = 840;
const int PauseButY = 29;
const int ContinueButX = 840;
const int ContinueButY = 29;

const int Text1X = 30;
const int Text1Y = 20;
const int Text2X = 30;
const int Text2Y = 80;
const int ScoreX = 260;
const int ScoreY = 20;
const int HighScoreX = 260;
const int HighScoreY = 80;

const double Layer1Speed = 0.1;
const double Layer2Speed = 0.25;
const double Layer3Speed = 0.5;
const double Layer4Speed = 0.75;
const double Layer5Speed = 1.0;

const int DinoFrames = 6;
const int BirdFrames = 8;
const int BackgroundLayer = 5;


enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void LogError(string msg, int error_code = SDL_ERROR);

