#ifndef BUTTON_H
#define BUTTON_H

#include "Common.h"
#include "BaseObject.h"

class Button
{
public:
    Button();
    ~Button();

    void setRect(const int x, const int y, const int width, const int height);
    ButtonSprite currentSprite;
    bool isInside(SDL_Event e);
    void Render(SDL_Rect* clip, SDL_Renderer* screen, BaseObject& texture);
private:
    SDL_Rect rect;
};

#endif // BUTTON_H


