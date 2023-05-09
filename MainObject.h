#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include <algorithm>
#include "Common.h"
#include "BaseObject.h"
#include "Enemy.h"
#include "Heart.h"
#include "Bullet.h"
#include "Support.h"
#include "Boss.h"

using namespace CommonFunc;

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum STATUS{
        LEFT = 0,
        CENTER = 1,
        RIGHT = 2
    };

    void Show(SDL_Renderer* des);
    void HandleInput(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* g_gun, bool& playMusic);
    SDL_Rect getRect();

    //void DoPlayer();
    void Check();
    void ChecktoEnemy(vector<Enemy*>& enemy, Heart& heart, Mix_Chunk* sound, bool& playMusic);
    void ChecktoBoss(vector<Boss*>& boss, Heart& heart, Mix_Chunk* sound, bool& playMusic);
    void CheckSupport(vector<Support*> sp, Heart& heart,
                      Mix_Chunk* sound, bool& play_music);
    void set_bullet_list(vector<Bullet*> bullet_list)
    {
        p_bullet_list = bullet_list;
    }
    std::vector<Bullet*> get_bullet_list()
    {
        return p_bullet_list;
    }
    int get_bullet_type() {return bullet_type;};
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int idx);
    void set_dead(bool e) {isDead = e;};
    //bool is_dead(){return isDead;};
    bool is_delete() {return isDelete;};
private:
    std::vector<Bullet*> p_bullet_list;
    int bullet_type;
    float x_val;
    float y_val;

    float xpos;
    float ypos;

    int width_frame;
    int height_frame;
    SDL_Rect main_frame[MAIN_FRAME];
    int frame;
    int exp_frame;
    //Input input_type;
    int status;
    bool isDead;
    bool isDelete;

};

#endif // MAIN_OBJECT_H


