#ifndef BULLET_H
#define BULLET_H

#include "BaseObject.h"
#include "Common.h"

class Bullet : public BaseObject
{
public:
    Bullet();
    ~Bullet();

    void set_x_val(const int& xVal) {x_val = xVal;}
    void set_y_val(const int& yVal) {y_val = yVal;}
    int get_x_val() {return x_val;}
    int get_y_val() {return y_val;}

    void set_is_move(const bool& isMove) {is_move = isMove;}
    bool get_is_move() {return is_move;}

    void setX(int X){x = X;}
    void setY(int Y) {y = Y;}

    int getX() {return x;}
    int getY() {return y;}

    SDL_Rect getRect();

    void HandleMove();
private:
    int x_val;
    int y_val;
    int x;
    int y;
    bool is_move;

};

#endif // BULLET_H

