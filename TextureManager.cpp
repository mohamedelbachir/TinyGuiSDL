#include"TextureManager.h"
#include<map>
#include<iostream>
TextureManager* TextureManager::s_pInstance=NULL;

TextureManager::TextureManager() {}

TextureManager::~TextureManager()
{
    cleanUp();
}

void TextureManager::cleanUp()
{
    std::map<std::string,SDL_Texture *>::iterator it;
    for(it=m_textureMap.begin(); it!=m_textureMap.end(); it++)
    {
        if(it->second!=NULL){
            std::cout<<"deleting texture : "<<it->first<<" ...";
            SDL_DestroyTexture(it->second);
            std::cout<<"Done"<<std::endl;
        }
    }
    std::cout<<"All Texture is Cleaned..."<<std::endl;
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id)
{
    if(m_textureMap[id]!=NULL)
    {
        SDL_DestroyTexture(m_textureMap[id]);
        std::map<std::string,SDL_Texture*>::iterator it=m_textureMap.find(id);
        m_textureMap.erase(it);
    }
    std::cout<<"suppression de  : "<<id<<std::endl;
}

bool TextureManager::load(std::string filepath, std::string id, SDL_Renderer* pRenderer)
{

    SDL_Texture *pTexture;
    pTexture=IMG_LoadTexture(pRenderer,filepath.c_str());
    if(pTexture==NULL)
    {
        return false;
    }
    m_textureMap[id]=pTexture;

    return true;
}

void TextureManager::draw(std::string id, float x, float y, int width, int height,SDL_Rect src,double angle,SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{


    SDL_FRect dstRect= {0};

    dstRect.x=x;
    dstRect.y=y;

    dstRect.w=width;
    dstRect.h=height;

    SDL_FPoint center={dstRect.w/2,dstRect.h/2};

    SDL_RenderCopyExF(pRenderer,m_textureMap[id],&src,&dstRect,angle,&center,flip);
}

SDL_Texture *TextureManager::getTextureMap(std::string id)
{
    return m_textureMap[id];
}

std::string TextureManager::getTextureIDMap(SDL_Texture *pTexture){

}

void TextureManager::setTexture(std::string id,SDL_Texture *newTexture)
{
    if(m_textureMap[id]!=NULL)
    {
        clearFromTextureMap(id);
    }
    if(newTexture==NULL){
        throw("Texture NULL !!!");
    }
    m_textureMap[id]=newTexture;

}

