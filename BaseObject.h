#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common.h"

using namespace std;

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    void SetRect(const int& x, const int& y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect(){
        return rect_;
    }
    int getWidth()
    {
        return rect_.w;
    }
    int getHeight()
    {
        return rect_.h;
    }
    bool loadIMG(std::string file_name, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, int x, int y, SDL_Rect* clip);
    void Free();
protected:
    SDL_Rect rect_;
    SDL_Texture* object;
};

#endif // BASE_OBJECT_H_



