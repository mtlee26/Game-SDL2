#include "BaseObject.h"

BaseObject::BaseObject()
{
    rect_.x = rect_.y = rect_.w = rect_.h = 0;
    object = nullptr;
}

bool BaseObject::loadIMG(std::string file_name, SDL_Renderer* screen)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadSurface = IMG_Load(file_name.c_str());
    if(loadSurface != nullptr)
    {
        //SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        if(newTexture != nullptr)
        {
            rect_.w = loadSurface->w;
            rect_.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    object = newTexture;
    return object != nullptr;
}

void BaseObject::Render(SDL_Renderer* des, int x, int y, SDL_Rect* clip)
{
    SDL_Rect destRect = {x, y, rect_.w, rect_.h};

    if(clip != NULL)
    {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }

    SDL_RenderCopy(des, object, clip, &destRect);
}


void BaseObject::Free()
{
    if(object != nullptr)
    {
        SDL_DestroyTexture(object);
        object = nullptr;
        rect_.w = 0;
        rect_.h = 0;
    }
}

BaseObject::~BaseObject()
{
    Free();
}











