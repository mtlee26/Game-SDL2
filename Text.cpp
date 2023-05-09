#include "Text.h"

Text::Text()
{
    text_color = {255, 255, 255};
}

Text::~Text()
{

}

void Text::set_color(int type)
{
    if(type == RED_TEXT) text_color = {255, 0, 0};
    else if(type == WHITE_TEXT) text_color = {255, 255, 255};
    else if(type == BLACK_TEXT) text_color = {0, 0, 0};
}

bool Text::loadFromRenderedText(TTF_Font *gFont, SDL_Renderer* screen)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text_.c_str(), text_color);

	if( textSurface == NULL )
	{
		return false;
	}
	else
	{
        object = SDL_CreateTextureFromSurface( screen, textSurface );
		if( object == NULL )
		{
			return false;
		}
		else
		{
			rect_.w = textSurface->w;
			rect_.h = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	return object != NULL;
}

void Text::Show(SDL_Renderer* screen)
{
    SDL_RenderCopy(screen, object, NULL, &rect_);
    //SDL_RenderPresent(screen);
};

bool Text::isInside(SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        int width = rect_.w;
        int height = rect_.h;

        bool inside = true;
        if(x < rect_.x)
        {
            inside = false;
        }
        else if(x > rect_.x + width)
        {
            inside = false;
        }
        else if(y < rect_.y)
        {
            inside = false;
        }
        else if(y > rect_.y + height)
        {
            inside = false;
        }
        return inside;
    }
    return false;
}
