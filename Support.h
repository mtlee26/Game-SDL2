#ifndef SUPPORT_H
#define SUPPORT_H

#include "Common.h"
#include "BaseObject.h"

class Support : public BaseObject
{
public:
    Support(int type_);
    ~Support();
    int get_type() {return type;}
    bool check_fall();
    void loadImg(string file_name, SDL_Renderer* screen);
    void Free();
    void Move();
    void Show(SDL_Renderer* screen);
    SDL_Rect getRect();
private:
    int type;
    int xpos;
    int ypos;
    int y_val;
    SDL_Texture* sp_object;
};

#endif // SUPPORT_H
