#include "Enemy.h"

Enemy::Enemy(int type_)
{
    type = type_;
    if(type == RED_ENEMY) health = 1;
    else if(type == GREEN_ENEMY) health = 2;
    x_val = 0;
    y_val = 0;
    xpos = rand() % (SCREEN_WIDTH-100);
    ypos = 0;
    frame = 0;
}

Enemy::~Enemy()
{
    Free();
}

void Enemy::HandleMove()
{
    x_val = 0;
    y_val = ENEMY_SPEED;

    xpos += x_val;
    ypos += y_val;

    if(ypos >= SCREEN_HEIGHT)
    {
        Free();
    }

}

bool Enemy::check_move()
{
    if(ypos >= SCREEN_HEIGHT) return true;
    return false;
}

void Enemy::Show(SDL_Renderer* des)
{
    Free();
    if(type == RED_ENEMY){
        loadIMG("IMG/red_enemy.png", des);
        frame++;
        if(frame >= ENEMY_FRAME) frame = 0;
        SDL_Rect clip = {frame*(GetRect().w/ENEMY_FRAME), 0, GetRect().w/ENEMY_FRAME, GetRect().h};
        SDL_Rect rect = {xpos, ypos, rect_.w/ENEMY_FRAME, rect_.h};
        SDL_RenderCopy(des, object, &clip, &rect);
    }
    else if(type == GREEN_ENEMY){
        loadIMG("IMG/green_enemy.png", des);
        frame++;
        if(frame >= ENEMY_FRAME) frame = 0;
        SDL_Rect clip = {frame*(GetRect().w/ENEMY_FRAME), 0, GetRect().w/ENEMY_FRAME, GetRect().h};
        SDL_Rect rect = {xpos, ypos, rect_.w/ENEMY_FRAME, rect_.h};
        SDL_RenderCopy(des, object, &clip, &rect);
    }
}

SDL_Rect Enemy::getRect()
{
    SDL_Rect tRect;
    tRect.x = get_xpos();
    tRect.y = get_ypos();
    tRect.w = GetRect().w/ENEMY_FRAME;
    tRect.h = GetRect().h;
    return tRect;
}

void Enemy::InitEnemyBullet(Bullet* e_bullet, SDL_Renderer* screen)
{
    if(e_bullet != nullptr)
    {
        e_bullet->loadIMG("IMG/laze_bullet.png", screen);
        e_bullet->set_is_move(true);
        e_bullet->setX(xpos + 8);
        e_bullet->setY(ypos + getRect().h);
        e_bullet->set_y_val(10);
        e_bullet_list.push_back(e_bullet);
    }
}

void Enemy::MakeBullet (SDL_Renderer* screen)
{
    for(int i = 0; i < e_bullet_list.size(); i++)
    {
        Bullet* e_bullet = e_bullet_list.at(i);
        if(e_bullet != nullptr){
            if(e_bullet->get_is_move()){
                e_bullet->HandleMove();
                e_bullet->Render(screen, e_bullet->getX(), e_bullet->getY(), NULL);
            }
            else{
                int random = rand() % 20;
                if(random == 1){
                    e_bullet->set_is_move(true);
                    e_bullet->setX(xpos+ 8);
                    e_bullet->setY(ypos + getRect().h);
                }
            }
        }
    }
}

void Enemy::ResetBullet(const int idx)
{
    Bullet* bullet = e_bullet_list.at(idx);
    if(bullet != nullptr)
    {
        bullet->set_is_move(true);
        bullet->setX(xpos + 8);
        bullet->setY(ypos + rect_.h);
    }
}



