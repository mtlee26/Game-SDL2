#ifndef BOSS_H
#define BOSS_H

#include "Common.h"
#include "BaseObject.h"
#include "Bullet.h"

class Boss : public BaseObject
{
public:
    Boss();
    ~Boss();

    float get_xpos() {return xpos;}
    float get_ypos() {return ypos;}

    void HandleMove();
    void Show(SDL_Renderer* des);

    SDL_Rect getRect();
    vector<Bullet*> get_bullet_list() {return boss_bullet_list;}
    //void set_bullet_list(vector<Bullet*> b_list) {boss_bullet_list = b_list;}
    void InitBossBullet(Bullet* e_bullet, SDL_Renderer* screen);
    void MakeBullet (SDL_Renderer* screen );
    void ResetBullet(const int idx);

    bool is_dead() {return health <= 0;};
    void decrease_health() {health--;};
    void set_isDead(bool e) {isDead = e;};
    bool is_delete() {return isDelete;};
private:
    int health;
    float xpos;
    float ypos;
    float x_val;
    float y_val;
    int direction;
    //SDL_Texture* enemy;
    int frame;
    bool isDead;
    int f;
    bool isDelete;
    vector<Bullet*> boss_bullet_list;

};

#endif // BOSS_H
