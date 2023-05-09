#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "Common.h"
#include "Button.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Text.h"

void RenderBackground(double& offsetSpeed, BaseObject& Background, SDL_Renderer* renderer);
void CreateEnemy(vector<Enemy*>& enemy, SDL_Renderer* screen);
void CheckEnemy(SDL_Renderer* screen, MainObject& player, vector<Enemy*>& enemy,
                Mix_Chunk* sound, bool& play_music, int& player_score);
void CheckBoss(SDL_Renderer* screen, MainObject& player, vector<Boss*>& boss,
                Mix_Chunk* sound, bool& play_music, int& player_score);

class Game
{
public:
    Game();
    ~Game();

    bool is_quit_menu;
    bool is_play;
    bool is_quit;
    bool is_win;
    bool play_music;
    bool is_paused;

    string GetHighScoreFromFile(string path);
    void UpdateHighScore(string path, const int& score);

    void Init(SDL_Renderer* screen);
    void handlePlayButton(SDL_Event e, Mix_Chunk* click);
    void handleHelpButton(SDL_Renderer* screen, SDL_Event e, Mix_Chunk* click);
    void handlePlayAgain(SDL_Event e, Mix_Chunk* click);
    void handleExitButton(SDL_Event e, Mix_Chunk* click);
    void handleExit(SDL_Event e, Mix_Chunk* click);
    void handlePause(SDL_Event e);
    void HandleEvent(SDL_Renderer* screen, SDL_Event e, Mix_Chunk* click);
    void RenderMenu(SDL_Renderer* screen);
    void handleEndGame(SDL_Renderer* screen, SDL_Event e, Mix_Chunk* click, TTF_Font* font, const int& player_score);
    void RenderPause(SDL_Renderer* screen);
    void FreeMenu();
private:
    Button PlayButton;
    Button HelpButton;
    Button ExitButton;
    Button BackButton;

    BaseObject menu;
    BaseObject help;
    BaseObject playButton;
    BaseObject helpButton;
    BaseObject exitButton;
    BaseObject backButton;
    BaseObject pause;

    SDL_Rect ButtonClip[2];
    SDL_Rect BackButtonClip[2];

    Text PlayAgain;
    Text Exit;

    Mix_Chunk* sound;
};

#endif // GAME_UTILS_H
