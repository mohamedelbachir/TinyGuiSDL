#include"FontManager.h"
#include<iostream>
fontManager* fontManager::s_pInstance=NULL;

fontManager::fontManager() {
    if(!TTF_WasInit()){
        TTF_Init();
    }
}

fontManager::~fontManager()
{
    cleanUp();
}

void fontManager::cleanUp()
{
    std::map<std::string,TTF_Font *>::iterator it;
    for(it=m_fontMap.begin(); it!=m_fontMap.end(); it++)
    {
        std::cout<<"Eraseing font "<<it->first<<"....";
        TTF_CloseFont(it->second);
        std::cout<<"Done!"<<std::endl;
    }
    std::cout<<"Clear Map"<<std::endl;
    m_fontMap.clear();
    std::cout<<"Done !!"<<std::endl;
    TTF_Quit();
}

void fontManager::clearFromFontMap(std::string id)
{
    if(m_fontMap[id]!=NULL)
    {
        TTF_CloseFont(m_fontMap[id]);
        std::map<std::string,TTF_Font*>::iterator it=m_fontMap.find(id);
        m_fontMap.erase(it);
    }
}

bool fontManager::load(std::string filepath,int t_size,std::string id)throw(std::string)
{
    TTF_Font*ft=TTF_OpenFont(filepath.c_str(),t_size);
    if(ft==NULL){
        std::cout<<"Impossible to Open the Font : "<<TTF_GetError();
        throw(TTF_GetError());
    }
    m_fontMap[id]=ft;
    return true;
}

TTF_Font *fontManager::getFontMap(std::string id)
{
    return m_fontMap[id];
}


