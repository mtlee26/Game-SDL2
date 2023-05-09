#ifndef ENEMY_H
#define ENEMY_H

#include "Common.h"
#include "BaseObject.h"
#include "Bullet.h"

#define type1 1
#define type2 2

class Enemy : public BaseObject
{
public:
    Enemy(int type_);
    ~Enemy();

    float get_xpos() {return xpos;}
    float get_ypos() {return ypos;}

    //void set_clip();
    void HandleMove();
    void Show(SDL_Renderer* des);

    int get_type() {return type;};
    SDL_Rect getRect();
    vector<Bullet*> get_bullet_list() {return e_bullet_list;}
    void set_bullet_list(vector<Bullet*> b_list) {e_bullet_list = b_list;}
    void InitEnemyBullet(Bullet* e_bullet, SDL_Renderer* screen);
    void MakeBullet (SDL_Renderer* screen );
    void ResetBullet(const int idx);
    bool is_dead() {return health <= 0;};
    void decrease_health() {health--;};
    bool check_move();
private:
    int health;
    int type;
    float xpos;
    float ypos;
    float x_val;
    float y_val;
    int frame;
    //SDL_Texture* enemy;
    vector<Bullet*> e_bullet_list;
};

#endif // ENEMY_H



