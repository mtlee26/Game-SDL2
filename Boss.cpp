#include "Boss.h"

Boss::Boss()
{
    health = 10;
    x_val = 0;
    y_val = 0;
    direction = rand() % 2;
    xpos = rand() % (SCREEN_WIDTH-100);
    ypos = 0;
    isDead = false;
    isDelete = false;
    f = 0;
    frame = 0;
}

Boss::~Boss()
{
    Free();
}

void Boss::HandleMove()
{
    if(direction == left_dir){
        x_val = -ENEMY_SPEED;
    }
    else if(direction == right_dir){
        x_val = ENEMY_SPEED;
    }
//    int rd = rand() % 2 + 2;
//    if(rd == up_dir) y_val = -ENEMY_SPEED;
//    else y_val = ENEMY_SPEED;
    y_val = rand() % 15 - 7;

    xpos += x_val;
    ypos += y_val;
    if(xpos < 0)
    {
        xpos = 0;
        direction = right_dir;
    }
    if(xpos + GetRect().w / BOSS_FRAME >= SCREEN_WIDTH)
    {
        xpos = SCREEN_WIDTH - GetRect().w / BOSS_FRAME;
        direction = left_dir;
    }
    if(ypos < 0)
    {
        ypos = 0;
    }
    if(ypos + GetRect().h >= SCREEN_HEIGHT - 200)
    {
        ypos = SCREEN_HEIGHT - 200 - GetRect().h;
    }
}

void Boss::Show(SDL_Renderer* des)
{
    Free();
    if(isDead){
        loadIMG("IMG/exp11.png", des);
        SDL_Rect tmp = {f * (GetRect().w / 10), 0, GetRect().w / 10, GetRect().h};
        Render(des, xpos, ypos - 10, &tmp);
        f++;
        if(f >= 10) isDelete = true;
    }
    else {
        loadIMG("IMG/health.png", des);
        SDL_Rect tmp = {0, (10-health) * GetRect().h/11, GetRect().w, GetRect().h / 11};
        Render(des, xpos, ypos - 10, &tmp);
        Free();
        loadIMG("IMG/boss.png", des);
        frame++;
        if(frame >= BOSS_FRAME) frame = 0;
        SDL_Rect clip = {frame*(GetRect().w/BOSS_FRAME), 0, GetRect().w/BOSS_FRAME, GetRect().h};
        SDL_Rect rect = {xpos, ypos, rect_.w/BOSS_FRAME, rect_.h};
        SDL_RenderCopy(des, object, &clip, &rect);
    }
}

SDL_Rect Boss::getRect()
{
    SDL_Rect tRect;
    tRect.x = get_xpos();
    tRect.y = get_ypos();
    tRect.w = GetRect().w / BOSS_FRAME;
    tRect.h = GetRect().h;
    return tRect;
}

void Boss::InitBossBullet(Bullet* e_bullet, SDL_Renderer* screen)
{
    if(e_bullet != nullptr && !isDead)
    {
        e_bullet->Free();
        e_bullet->loadIMG("IMG/boss_bullet.png", screen);
        e_bullet->set_is_move(true);
        e_bullet->setX(xpos + 40);
        e_bullet->setY(ypos + GetRect().h);
        e_bullet->set_x_val(0);
        e_bullet->set_y_val(20);
        boss_bullet_list.push_back(e_bullet);
    }
}

void Boss::MakeBullet (SDL_Renderer* screen)
{
    for(int i = 0; i < boss_bullet_list.size(); i++)
    {
        Bullet* e_bullet = boss_bullet_list.at(i);
        if(e_bullet != nullptr && !isDead){
            if(e_bullet->get_is_move()){
                e_bullet->HandleMove();
                e_bullet->Render(screen, e_bullet->getX(), e_bullet->getY(), NULL);
            }
            else{
                e_bullet->set_is_move(true);
                e_bullet->setX(xpos);
                e_bullet->setY(ypos + GetRect().h);
            }
        }
    }
}

void Boss::ResetBullet(const int idx)
{
    Bullet* bullet = boss_bullet_list.at(idx);
    if(bullet != nullptr)
    {
        bullet->set_is_move(true);
        bullet->setX(xpos+40);
        bullet->setY(ypos + GetRect().h);
    }
}




