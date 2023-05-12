#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

static SDL_Window* window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event event;
static Mix_Chunk* g_click = nullptr;
static Mix_Chunk* g_gun = nullptr;
static Mix_Chunk* g_hit1 = nullptr;
static Mix_Chunk* g_hit2 = nullptr;
static TTF_Font* g_font1 = NULL;
static TTF_Font* g_font2 = NULL;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 630;
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 98;
const int BACK_BUTTON_WIDTH = 75;
const int BACK_BUTTON_HEIGHT = 59;

const int PLAY_XPOS = 150;
const int PLAY_YPOS = 400;
const int HELP_XPOS = 425;
const int HELP_YPOS = 400;
const int PLAYAGAIN_XPOS = 180;
const int PLAYAGAIN_YPOS = 350;
const int EXIT_XPOS1 = 700;
const int EXIT_YPOS1 = 400;
const int EXIT_XPOS2 = 680;
const int EXIT_YPOS2 = 350;
const int BACK_XPOS = 20;
const int BACK_YPOS = 20;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

const int ENEMY_HEIGHT = 85;
const float ENEMY_SPEED = 5;
const int ENEMY_FRAME = 8;
const int BOSS_FRAME = 8;

const int FRAME_PER_SECOND = 40;//fps

#define WIDTH_MAIN_OBJECT 100//50
#define HEIGHT_MAIN_OBJECT 85//74
#define MAIN_FRAME 8
#define MAIN_BULLET_SPEED 25
#define HEART 3

#define PLAYER_SPEED 6
#define SUPPORT_FALL 6

#define SUPPORT_WIDTH 25
#define SUPPORT_HEIGHT 25

#define right_dir 0
#define left_dir 1
#define up_dir 2
#define down_dir 3

#define round_bullet 0
#define laze_bullet 1

#define bullet_change 0
#define heart_plus 1

#define RED_ENEMY 0
#define GREEN_ENEMY 1

enum ButtonSprite
{
    BUTTON_MOUSE_OUT = 0,
    BUTTON_MOUSE_OVER = 1
};

namespace CommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, SDL_Rect& object2);
}

#endif // COMMON_FUNCTION_H




