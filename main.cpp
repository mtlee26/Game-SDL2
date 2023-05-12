#include "Common.h"
#include "Game_Utils.h"
#include "Button.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Heart.h"
#include "Text.h"
#include "Boss.h"
#include "Support.h"

#include <ctime>

using namespace std;
using namespace CommonFunc;

BaseObject g_background;

Game game;

bool init();
bool loadMedia();
void Close();


int main (int argc, char* argv[])
{
    Uint32 frameStart;
    if(!init()) return -1;

    if(!loadMedia())return -1;

    game.Init(g_screen);

    while(!game.is_quit_menu)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                game.is_quit_menu = true;
                break;
            }
            game.HandleEvent(g_screen, event, g_click);
        }
        game.RenderMenu(g_screen);
    }

    while(game.is_play)
    {
        srand(time(NULL));

        double offsetSpeed = 0;

        MainObject player;
        player.loadIMG("player.png", g_screen);

        Heart heart;
        heart.Init(g_screen);

        Text score;
        score.set_color(Text::WHITE_TEXT);
        score.SetRect(400, 10);

        Text high_score;
        high_score.set_color(Text::WHITE_TEXT);
        high_score.SetRect(700, 10);

        Text end_score;
        end_score.set_color(Text::WHITE_TEXT);
        end_score.SetRect(300, 120);

        Text end_HighScore;
        end_HighScore.set_color(Text::WHITE_TEXT);
        end_HighScore.SetRect(300, 220);

        string score_str;
        string highscore;

        int player_score = 0;

        vector<Support*> sp_list;

        vector<Enemy*> enemy;
        vector<Boss*> boss;

        Uint32 start_time = SDL_GetTicks();

        while(!game.is_quit){
            frameStart = SDL_GetTicks();
            while(SDL_PollEvent(&event) != 0)
            {
                if(event.type == SDL_QUIT)
                {
                    game.is_play = false;
                    game.is_quit = true;
                    break;
                }
                game.handlePause(event);
                player.HandleInput(event, g_screen, g_gun, game.play_music);
            }
            game.RenderPause(g_screen);

            if(!game.is_paused){

            SDL_RenderClear(g_screen);

            RenderBackground(offsetSpeed, g_background, g_screen);

            Uint32 time = SDL_GetTicks();

            if(enemy.size() <= 20) CreateEnemy(enemy, g_screen);

            int rd = rand() % 1200;
            if(rd == 1 && boss.size() < 2 && player_score >= 200){
                Boss* new_boss = new Boss();
                Bullet* b_bullet = new Bullet();
                new_boss->InitBossBullet(b_bullet, g_screen);
                boss.push_back(new_boss);
            }

            if(time - start_time >= 30000)
            {
                Support* sp_object = new Support(rand() % 2);
                sp_list.push_back(sp_object);
                start_time = time;
            }

            CheckEnemy(g_screen, player, enemy, g_hit2, game.play_music, player_score);
            CheckBoss(g_screen, player, boss, g_hit2, game.play_music, player_score);

            player.ChecktoEnemy(enemy, heart, g_hit1, game.play_music);
            player.ChecktoBoss(boss, heart, g_hit1, game.play_music);
            player.CheckSupport(sp_list, heart, g_click, game.play_music);

            for(int i = 0; i < sp_list.size(); i++)
            {
                if(sp_list[i] != nullptr)
                {
                    sp_list[i]->Move();
                    sp_list[i]->Show(g_screen);
                }
                if(sp_list[i]->check_fall())
                {
                    sp_list.erase(sp_list.begin()+i);
                    sp_list[i] = nullptr;
                }
            }

            for(int i = 0; i < enemy.size(); i++)
            {
                if(enemy[i] != nullptr && !enemy[i]->is_dead())
                {
                    enemy[i]->HandleMove();
                    enemy[i]->MakeBullet(g_screen);
                    enemy[i]->Show(g_screen);
                }
                if(enemy[i]->check_move()){
                    enemy.erase(enemy.begin()+i);
                    enemy[i]->Free();
                }
            }

            for(int i = 0; i < boss.size(); i++)
            {
                if(boss[i] != nullptr)
                {
                    boss[i]->HandleMove();
                    boss[i]->MakeBullet(g_screen);
                    boss[i]->Show(g_screen);
                }
                if(boss[i]->is_delete()){
                    boss.erase(boss.begin() + i);
                    boss[i]->Free();
                }
            }

            player.HandleBullet(g_screen);
            player.Check();
            player.Show(g_screen);

            heart.Show(g_screen);

            score_str = "SCORE: ";
            string val_str = to_string(player_score);
            score_str += val_str;

            score.Free();
            score.set_text(score_str);
            score.loadFromRenderedText(g_font1, g_screen);
            score.Show(g_screen);

            highscore = "HIGH SCORE: ";
            string high = game.GetHighScoreFromFile("HighScore.txt");
            highscore += high;

            high_score.Free();
            high_score.set_text(highscore);
            high_score.loadFromRenderedText(g_font1, g_screen);
            high_score.Show(g_screen);

            game.UpdateHighScore("HighScore.txt", player_score);

            if(heart.getHeart() == 0 )
            {
                game.is_quit = true;
            }

            SDL_RenderPresent(g_screen);
            int real_time = SDL_GetTicks() - frameStart;
            int time_one_frame = 1000/FRAME_PER_SECOND; //ms
            if(real_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_time;
                if(delay_time >= 0)
                    SDL_Delay(delay_time);
            }
        }
        }
        enemy.clear();
        boss.clear();
        player.Free();

        if(game.is_play)
        {
            end_score.set_text(score_str);
            end_score.loadFromRenderedText(g_font2, g_screen);
            end_score.Show(g_screen);

            end_HighScore.set_text(highscore);
            end_HighScore.loadFromRenderedText(g_font2, g_screen);
            end_HighScore.Show(g_screen);

            game.handleEndGame(g_screen, event, g_click, g_font2, player_score);
        }
        else{
            score.Free();
            high_score.Free();
            g_background.Free();
        }
    }
    game.~Game();
    g_background.Free();

    Close();
    return 0;
}

bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    window = SDL_CreateWindow("Let's play!", SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        return false;
    }
    else{
        g_screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == nullptr){
            return false;
        }
        else{
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags)) return false;
        }
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        return false;
    if(TTF_Init() == -1) return false;
    else{
        g_font1 = TTF_OpenFont("font.ttf", 25);
        if(g_font1 == NULL) return false;
        g_font2 = TTF_OpenFont("font1.ttf", 50);
        if(g_font2 == NULL) return false;
    }
    return true;
}

bool loadMedia()
{
    bool success = true;
    g_background.loadIMG("IMG/bg.png", g_screen);
    g_gun = Mix_LoadWAV("sound/gun.wav");
    g_hit1 = Mix_LoadWAV("sound/bom.wav");
    g_hit2 = Mix_LoadWAV("sound/gun4.wav");
    g_click = Mix_LoadWAV("sound/click.wav");

    if(g_gun == nullptr || g_hit1 == nullptr || g_hit2 == nullptr)
        success = false;
    return success;
}

void Close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}








