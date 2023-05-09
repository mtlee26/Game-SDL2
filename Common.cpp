#include "Common.h"

bool CommonFunc::CheckCollision(const SDL_Rect& object1, SDL_Rect& object2)
{
    int left_1 = object1.x;
    int right_1 = object1.x + object1.w;
    int top_1 = object1.y;
    int bottom_1 = object1.y + object1.h;

    int left_2 = object2.x;
    int right_2 = object2.x + object2.w;
    int top_2 = object2.y;
    int bottom_2 = object2.y+object2.h;

    if(left_1 >= left_2 && left_1 <= right_2)
    {
        if(top_1 >= top_2 && top_1 <= bottom_2)
            return true;
        if(bottom_1 >= top_2 && bottom_1 <= bottom_2)
            return true;
        if(top_1 <= top_2 && bottom_2 <= bottom_1)
            return true;
    }
    if(left_1)
    if(right_1 >= left_2 && right_1 <= right_2)
    {
        if(top_1 >= top_2 && top_1 <= bottom_2)
            return true;
        if(bottom_1 >= top_2 && bottom_1 <= bottom_2)
            return true;
        if(top_1 <= top_2 && bottom_2 <= bottom_1)
            return true;
    }

    return false;
}






