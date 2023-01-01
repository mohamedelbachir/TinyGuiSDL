#ifndef UI_BUTTON_H_INCLUDED
#define UI_BUTTON_H_INCLUDED
#include"Texture.h"
#include"UI_Text.h"
class UI_Button:public Texture{
private:
    UI_Text *btn_label;
    void startContentUpdate()override;
public:
    static int instance;

    UI_Button(SDL_Renderer *rendu,std::string idfont,std::string texteButton,int x,int y);

    ~UI_Button();

    void update()override;


    void draw(SDL_Renderer *pRenderer)override;

    void setSourceDisplay(SDL_Rect src);

    void setBorderRadius(int rad);

    UI_Text* getTextButton();

    void clean() override;

};



#endif // UI_BUTTON_H_INCLUDED
