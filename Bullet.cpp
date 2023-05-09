#include "Bullet.h"

Bullet::Bullet()
{
    x_val = 0;
    y_val = 0;
    x = 0;
    y = 0;
    is_move = false;
}

Bullet::~Bullet()
{

}

SDL_Rect Bullet::getRect()
{
    SDL_Rect b_rect;
    b_rect.x = getX();
    b_rect.y = getY();
    b_rect.w = GetRect().w;
    b_rect.h = GetRect().h;
    return b_rect;
}

void Bullet::HandleMove()
{
    x += x_val;
    y += y_val;
    if(x < 0) is_move = false;
    else if(x > SCREEN_WIDTH) is_move = false;
    if(y < 0) is_move = false;
    else if(y > SCREEN_HEIGHT) is_move = false;
}


