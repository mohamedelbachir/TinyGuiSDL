#include"UI_Button.h"
#include<sstream>
#include"InputManager.h"

int UI_Button::instance=0;

UI_Button::UI_Button(SDL_Renderer *rendu,std::string idfont,std::string texteButton,int x,int y):Texture("",x,y)
{
    isTargetTexture=true;
    refRender=rendu;

    std::stringstream ss;
    ss<<instance++;

    std::string textNumber;
    ss>>textNumber;

    ID="button "+textNumber;

    btn_label=new UI_Text(rendu,texteButton,0,0,idfont);
    btn_label->setPositionMouseRelative(m_posMouseRef);

    resize(btn_label->getWidth()+20,btn_label->getHeight());

    m_src= {0,0,btn_label->getWidth(),btn_label->getHeight()};
    Texture::update();
}

UI_Button::~UI_Button()
{
    if(btn_label!=NULL){
        btn_label->clean();
    }
    clean();
}

void UI_Button::startContentUpdate(){
    Texture::startContentUpdate();
        btn_label->draw(refRender);
}

void UI_Button::update()
{
    //if(){
        btn_label->getVector()->setX(m_width/2-btn_label->getWidth()/2);
        btn_label->getVector()->setY(m_height/2-btn_label->getHeight()/2);
    //}
    btn_label->update();
    Texture::update();
}
UI_Text *UI_Button::getTextButton(){
    return btn_label;
}

void UI_Button::draw(SDL_Renderer *pRenderer)
{
    Texture::draw(pRenderer);
}
void UI_Button::setBorderRadius(int rad){
    m_rad=rad;
}
void UI_Button::clean()
{
    TextureManager::Instance()->clearFromTextureMap(ID);
}
