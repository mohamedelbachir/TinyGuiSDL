#include"UI_Text.h"
#include"FontManager.h"
#include<sstream>
int UI_Text::instance=0;

UI_Text::UI_Text(SDL_Renderer *rendu,std::string texte,int x,int y,std::string fontId):Texture("",x,y)
{
    std::stringstream ss;
    ss<<instance++;

    std::string textNumber;
    ss>>textNumber;

    ID="texte "+textNumber;

    this->fontID=fontId;

    refRender=rendu;

    changeTexte(texte);

    setColorState(0,0,0,255,MOUSE_OUT);
    setColorState(0,0,0,255,MOUSE_HOVER);
    setColorState(0,0,0,255,CLICKED);

}

UI_Text::~UI_Text()
{
    clean();
}

void UI_Text::update()
{
    Texture::update();
}

void UI_Text::draw(SDL_Renderer *pRenderer)
{
    if(refRender==NULL){
        refRender=pRenderer;
    }
    m_src= {0,0,m_width,m_height};
    SDL_SetTextureColorMod(theTextureManager::Instance()->getTextureMap(ID),fcolor[m_currentFrame].r,fcolor[m_currentFrame].g,fcolor[m_currentFrame].b);
    Texture::draw(pRenderer);
}


void UI_Text::clean()
{
    theTextureManager::Instance()->clearFromTextureMap(ID);
}

void UI_Text::changeTexte(std::string texte)
{
    SDL_Color nativeColor= {255,255,255,255};
    int val=wrapLength(texte);
    Uint32 wrap=0;
    if(val!=0)
    {
        int w,h;
        TTF_SizeText(thefontManager::Instance()->getFontMap(fontID),"O",&w,&h);
        wrap=(2*w+ ++val +2*h)*TTF_FontHeight(thefontManager::Instance()->getFontMap(fontID))/w;
        m_size=wrap;
    }
    this->texte=texte;

    if(refRender!=NULL){

        SDL_Surface *t_surface=(wrap!=0)? TTF_RenderText_Blended_Wrapped(thefontManager::Instance()->getFontMap(fontID),texte.c_str(),nativeColor,wrap)
                                        : TTF_RenderText_Blended(thefontManager::Instance()->getFontMap(fontID),texte.c_str(),nativeColor);

        SDL_Texture *texture = SDL_CreateTextureFromSurface(refRender,
                               t_surface);


        theTextureManager::Instance()->setTexture(ID,texture);

        SDL_QueryTexture(texture,NULL, NULL,&m_width, &m_height);

        SDL_FreeSurface(t_surface);
    }
}

void UI_Text::changeTexte(int val)
{

    std::stringstream ss;
    ss<<val;

    std::string txt;
    ss>>txt;

    changeTexte(txt);
}

void UI_Text::setFontText(std::string fontPath)
{
    if(thefontManager::Instance()->getFontMap(fontPath)!=NULL)
    {
        fontID=fontPath;
        changeTexte(texte);
    }
}
