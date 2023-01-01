#pragma once
#include"Vector2D.h"
#include"TextureManager.h"
#include"Widget.h"
#include<sstream>

#include"SDL2_gfxPrimitives.h"
class Texture:public Widget
{
private:
protected:
    SDL_Rect m_src={0};
    SDL_Renderer *refRender=NULL;
    bool hasSourceRectConstraint=false;
    bool isTargetTexture=false;

    //fonction for widget targetTexture updating
    virtual void startContentUpdate(){

        SDL_SetRenderTarget(refRender,NULL);
        SDL_SetRenderTarget(refRender,theTextureManager::Instance()->getTextureMap(ID));
        SDL_SetRenderDrawColor(refRender,255,255,255,0);
        SDL_RenderClear(refRender);
            SDL_RenderFillRect(refRender,NULL);
            if(m_rad>=2){
                roundedBoxRGBA(refRender,0,m_height-1,m_width-1,0,m_rad,fcolor[m_currentFrame].r,fcolor[m_currentFrame].g,fcolor[m_currentFrame].b,fcolor[m_currentFrame].a);
                roundedRectangleRGBA(refRender,0,m_height-1,m_width-1,0,m_rad,bcolor[m_currentFrame].r,bcolor[m_currentFrame].g,bcolor[m_currentFrame].b,bcolor[m_currentFrame].a);
            }else{
                const SDL_Rect r={0,0,m_width,m_height};
                //fill rectangle box
                SDL_SetRenderDrawColor(refRender,fcolor[m_currentFrame].r,fcolor[m_currentFrame].g,fcolor[m_currentFrame].b,fcolor[m_currentFrame].a);
                SDL_RenderFillRect(refRender,&r);

                //border of rectangle
                SDL_SetRenderDrawColor(refRender,bcolor[m_currentFrame].r,bcolor[m_currentFrame].g,bcolor[m_currentFrame].b,bcolor[m_currentFrame].a);
                SDL_RenderDrawRect(refRender,&r);
            }
    }
    virtual void endContentUpdate(){
        SDL_SetRenderTarget(refRender,NULL);
    }

    virtual void onContentUpdate(){}

public:
    static int instance;
    Texture(float px,float py,int pw,int ph,SDL_Renderer *pRenderer,std::string pRefnom):Texture(pRefnom,px,py)
    {
        std::stringstream ss;
        ss<<instance++;

        std::string textNumber;
        ss>>textNumber;

        ID=pRefnom+textNumber;

        refRender=pRenderer;
        m_width=pw;
        m_height=ph;

        try
        {
            theTextureManager::Instance()->setTexture(ID,SDL_CreateTexture(pRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,m_width,m_height));
        }
        catch(std::string e)
        {
            std::cout<<"Erreur : "<<e<<std::endl;
        }
        m_src= {0,0,m_width,m_height};
        isTargetTexture=true;

    }
    Texture(std::string pId,float px,float py)
    {
        m_callback=nullptr;
        m_position=Vector2D(px,py);
        m_posMouseRef=&m_position;
        ID=pId;
    }

    void resize(int w,int h)override
    {
        if(isTargetTexture){
            if(w>0&&h>0)
            {
                SDL_Texture *texture=SDL_CreateTexture(refRender,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,w,h);
                theTextureManager::Instance()->setTexture(ID,texture);
            }
        }else{
            Widget::resize(w,h);
        }
        update();
    }

    void update()override
    {
        if(m_display){
            Widget::update();
            if(isTargetTexture){

                startContentUpdate();
                    onContentUpdate();
                endContentUpdate();

                m_src.w=m_width;
                m_src.h=m_height;
                SDL_QueryTexture(theTextureManager::Instance()->getTextureMap(ID),NULL,NULL,&m_width,&m_height);
            }
        }else{
            checkEventToUpdate();
        }
    }

    void draw(SDL_Renderer *pRenderer)override
    {
        if(m_display){
            SDL_SetTextureBlendMode(theTextureManager::Instance()->getTextureMap(ID),SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(theTextureManager::Instance()->getTextureMap(ID),m_opacity);
            theTextureManager::Instance()->draw(ID,m_position.getX(),m_position.getY()
                                                ,m_width,m_height,m_src,m_angle,pRenderer,m_flip);
        }
    }
    void resizeShape(int w=-1,int h=-1)
    {
        if(h>=0)
        {
            setHeight(h);
        }
        if(w>=0)
        {
            setWidth(w);
        }
    }
    void setWidth(int w)
    {
        resize(w,m_height);
    }
    void addWidth(int w)
    {
        resize(m_width+w,m_height);
    }
    void setHeight(int h)
    {
        resize(m_width,h);
    }
    void addHeight(int h)
    {
        resize(m_width,m_height+h);
    }
};
