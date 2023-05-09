#include "Button.h"

Button::Button()
{
    rect.x = 0;
    rect.y = 0;
    rect.h = 0;
    rect.w = 0;

    currentSprite = BUTTON_MOUSE_OUT;
}

Button::~Button()
{

}

void  Button::setRect(const int x, const int y, const int width, const int height)
{
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
}

bool Button::isInside(SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        int width = rect.w;
        int height = rect.h;

        bool inside = true;
        if(x < rect.x)
        {
            inside = false;
        }
        else if(x > rect.x + width)
        {
            inside = false;
        }
        else if(y < rect.y)
        {
            inside = false;
        }
        else if(y > rect.y + height)
        {
            inside = false;
        }
        return inside;
    }
    return false;
}

void Button::Render(SDL_Rect* clip, SDL_Renderer* screen, BaseObject& texture)
{
    texture.Render(screen, rect.x, rect.y, clip);
}



