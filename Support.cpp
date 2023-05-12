#include "Support.h"

Support::Support(int type_)
{
    xpos = rand() % (SCREEN_WIDTH-200);
    ypos = 0;
    type = type_;
    y_val = 0;
    sp_object = nullptr;
}

Support::~Support()
{

}

void Support::Free()
{
    xpos = 0;
    ypos = 0;
    type = -1;
    if(sp_object != nullptr)
    {
        SDL_DestroyTexture(sp_object);
        sp_object = nullptr;
    }
}

bool Support::check_fall()
{
    if(ypos >= SCREEN_HEIGHT)
    {
        return true;
    }
    return false;
}

void Support::loadImg(string file_name, SDL_Renderer* screen)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadSurface = IMG_Load(file_name.c_str());
    if(loadSurface != nullptr)
    {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        SDL_FreeSurface(loadSurface);
    }
    sp_object = newTexture;
}

void Support::Move()
{
    y_val = SUPPORT_FALL;
    ypos += y_val;
    if(ypos >= SCREEN_HEIGHT)
    {
        Free();
    }
}

void Support::Show(SDL_Renderer* screen)
{
    if(type == bullet_change)
    {
        loadImg("IMG/x2.png", screen);
    }
    else if(type == heart_plus)
    {
        loadImg("IMG/heart1.png", screen);
    }
    SDL_Rect dRect = {xpos, ypos, SUPPORT_WIDTH, SUPPORT_HEIGHT};
    SDL_RenderCopy(screen, sp_object, NULL, &dRect);
}

SDL_Rect Support::getRect()
{
    SDL_Rect rect;
    rect.x = xpos;
    rect.y = ypos;
    rect.w = SUPPORT_WIDTH;
    rect.h = SUPPORT_HEIGHT;
    return rect;
}


