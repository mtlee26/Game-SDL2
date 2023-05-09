#include "Heart.h"

Heart::Heart()
{
    heart = 0;
}

Heart::~Heart()
{

}

void Heart::AddPos(const int& xpos)
{
    heart_pos.push_back(xpos);
}

void Heart::Show(SDL_Renderer* screen)
{
    for(int i = 0; i < heart_pos.size(); i++)
    {
        rect_.x = heart_pos.at(i);
        rect_.y = 0;
        Render(screen, rect_.x, rect_.y, NULL);
    }
}

void Heart::Init(SDL_Renderer* screen)
{
    heart = 3;
    loadIMG("IMG/heart1.png", screen);
    if(heart_pos.size() != 0)
    {
        heart_pos.clear();
    }
    AddPos(20);
    AddPos(50);
    AddPos(80);
}

void Heart::Decrease()
{
    heart--;
    heart_pos.pop_back();
}

void Heart::Increase()
{
    heart++;
    int size = heart_pos.size();
    heart_pos.push_back(heart_pos[size-1] + 30);
}
