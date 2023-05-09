#ifndef TEXT_H_
#define TEXT_H_
#include"BaseObject.h"
#include"Common.h"

class Text: public BaseObject
{
public:
    Text();
    ~Text();

    enum TextColor{
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    void set_color(int type);
    void set_text(string text_string) {text_ = text_string;};
    void Show(SDL_Renderer* screen);
    bool isInside(SDL_Event e);
    //void ShowNum (TTF_Font *gFont, SDL_Color textColor, SDL_Renderer* screen);
//    void SetValue(int val) {value = val ;} ;
//    int GetValue(){return value;} ;
//    void IncreaseValue(int x) {
//        value += x;
//        if (value <= 0) value = 0;
//    };
    bool loadFromRenderedText(TTF_Font *gFont, SDL_Renderer* screen);
    //string ConvertIntToString();
private:
    SDL_Color text_color;
    string text_;
    //int value;
};
#endif // GAMETEXT_H_
