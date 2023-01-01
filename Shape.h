#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
#include"Widget.h"
#include"SDL2_gfxPrimitives.h"
class Shape:public Widget{
public:
    Shape(float x,float y){
        m_position=Vector2D(x,y);
    }
    ~Shape(){}
};
class UI_Rect:public Shape{
public:
    UI_Rect(float x,float y,int w,int h):Shape(x,y){
        m_width=w;
        m_height=h;
    }
    void draw(SDL_Renderer *pRenderer)override{
        if(m_rad>=2){
            roundedBoxRGBA(pRenderer,m_position.getX(),m_position.getY(),m_position.getX()+m_width-1,m_position.getY()+m_height-1,m_rad,fcolor[m_currentFrame].r,fcolor[m_currentFrame].g,fcolor[m_currentFrame].b,fcolor[m_currentFrame].a);
            roundedRectangleRGBA(pRenderer,m_position.getX(),m_position.getY(),m_position.getX()+m_width-1,m_position.getY()+m_height-1,m_rad,bcolor[m_currentFrame].r,bcolor[m_currentFrame].g,bcolor[m_currentFrame].b,bcolor[m_currentFrame].a);
        }else{
            const SDL_FRect r={m_position.getX(),m_position.getY(),m_width,m_height};
            //fill rectangle box
            SDL_SetRenderDrawColor(pRenderer,fcolor[m_currentFrame].r,fcolor[m_currentFrame].g,fcolor[m_currentFrame].b,fcolor[m_currentFrame].a);
            SDL_RenderFillRectF(pRenderer,&r);

            //border of rectangle
            SDL_SetRenderDrawColor(pRenderer,bcolor[m_currentFrame].r,bcolor[m_currentFrame].g,bcolor[m_currentFrame].b,bcolor[m_currentFrame].a);
            SDL_RenderDrawRectF(pRenderer,&r);
        }
    }
};
class UI_Cercle:public Shape{
public:
    UI_Cercle(float x,float y,int r):Shape(x,y){
        m_rad=r;
        m_width=r*2;
        m_height=r*2;
    }
    void draw(SDL_Renderer *pRenderer)override{
        filledCircleRGBA(pRenderer,m_position.getX()+m_rad,m_position.getY()+m_rad,m_rad,fcolor[m_currentFrame].r,fcolor[m_currentFrame].g,fcolor[m_currentFrame].b,fcolor[m_currentFrame].a);
        circleRGBA(pRenderer,m_position.getX()+m_rad,m_position.getY()+m_rad,m_rad,bcolor[m_currentFrame].r,bcolor[m_currentFrame].g,bcolor[m_currentFrame].b,bcolor[m_currentFrame].a);
    }
};

class UI_Trigon:public Shape{
private:
    SDL_FPoint *r;
public:
    UI_Trigon(float x,float y,SDL_FPoint rect[3]):Shape(x,y){
        r=new SDL_FPoint[3];
        for(int i=0;i<3;i++){
            //std::cout<<"["<<r[i].x<<"] ";
            r[i]=rect[i];
        }
    }
    void draw(SDL_Renderer *pRenderer)override{
        trigonRGBA(pRenderer,r[0].x,r[0].y,r[1].x,r[1].y,r[2].x,r[2].y,fcolor[m_currentFrame].r,fcolor[m_currentFrame].g,fcolor[m_currentFrame].b,fcolor[m_currentFrame].a);
        filledTrigonRGBA(pRenderer,r[0].x,r[0].y,r[1].x,r[1].y,r[2].x,r[2].y,bcolor[m_currentFrame].r,bcolor[m_currentFrame].g,bcolor[m_currentFrame].b,bcolor[m_currentFrame].a);
    }
};

#endif // SHAPE_H_INCLUDED
