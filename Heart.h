#ifndef HEART_H
#define HEART_H

#include "Common.h"
#include "BaseObject.h"

class Heart : public BaseObject
{
public:
    Heart();
    ~Heart();

    int getHeart() {return heart;}
    void AddPos(const int& xpos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);
    void Decrease();
    void Increase();
private:
    int heart;
    vector<int> heart_pos;
};


#endif // HEART_H
