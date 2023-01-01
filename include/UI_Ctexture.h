#ifndef UI_CTEXTURE_H_INCLUDED
#define UI_CTEXTURE_H_INCLUDED
#include "Texture.h"
#include<vector>
class UI_Ctexture:public Texture{
private:
    std::function<void()>m_callback_onContentUpdate;

    std::vector<Widget *>widget_contener;
    void startContentUpdate()override;

    void onContentUpdate()override{
        if(m_callback_onContentUpdate!=nullptr){
            m_callback_onContentUpdate();
        }
    }
    SDL_Rect viewPort={0};
public:
    static int instance;

    UI_Ctexture(SDL_Renderer *rendu,int x,int y,int w,int h);

    ~UI_Ctexture();

    void addWidget(Widget *t);

    void setOnContentUpdate(std::function<void()>func){
        m_callback_onContentUpdate=func;
    }

    void update()override;

    void draw(SDL_Renderer *pRenderer)override;

    void clean() override;

};


#endif // UI_CTEXTURE_H_INCLUDED
