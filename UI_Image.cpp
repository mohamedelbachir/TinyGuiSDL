#include"UI_Image.h"
#include<sstream>
int UI_Image::instance=0;

UI_Image::UI_Image(std::string idImage,int x,int y):Texture("",x,y)
{
    std::stringstream ss;
    ss<<instance++;

    std::string textNumber;
    ss>>textNumber;

    ID="image "+textNumber;
    try
    {
        SDL_QueryTexture(theTextureManager::Instance()->getTextureMap(idImage),NULL,NULL,&m_width,&m_height);
    }
    catch(std::string e)
    {
        std::cout<<"Error : "<<e<<std::endl;
        exit(EXIT_FAILURE);
    }
    theTextureManager::Instance()->setTexture(ID,theTextureManager::Instance()->getTextureMap(idImage));
    m_src= {0,0,m_width,m_height};
}

UI_Image::UI_Image(std::string idImage,int x,int y,int srcw,int srch):UI_Image(idImage,x,y)
{
    hasSourceRectConstraint=true;
    m_src= {0,0,srcw,srch};
    m_width=srcw;
    m_height=srch;
}


UI_Image::UI_Image(std::string idImage,int x,int y,int srcx,int srcy, int srcw,int srch):UI_Image(idImage,x,y,srcw,srch)
{
    m_src.x=srcx;
    m_src.y=srcy;
}

UI_Image::~UI_Image()
{
    clean();
}

void UI_Image::update()
{
    Texture::update();
}

void UI_Image::draw(SDL_Renderer *pRenderer)
{
    Texture::draw(pRenderer);
}

void UI_Image::setSourceDisplay(SDL_Rect src)
{
    this->m_src=src;
}

void UI_Image::clean()
{
    TextureManager::Instance()->clearFromTextureMap(ID);
}
