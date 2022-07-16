#ifndef GUI_BUTTON_H_INCLUDED
#define GUI_BUTTON_H_INCLUDED
///spacement entre icon et la bordure
#define SPACEBORDUREICON 5

///spacement entre texte et la bordure
#define SPACEBORDURETEXT 5

///taille de icon de button (max)
#define ICONBUTTONSIZE 18

#include"GUI_svg.h"
#include "GUI_Shape.h"
class GUI_button:public GUI_Shape{
protected:

    GUI_Texte *btn_name;
    SDL_Rect spaceText={0};
    GUI_Image *icone=nullptr;

public:

    ///Destructeur de Button
    ~GUI_button(){

        /**Suppression de Button*/
        if(btn_name!=nullptr){
            btn_name=nullptr;
            delete btn_name;
        }
        if(icone!=nullptr){
            delete icone;
        }
    }

    /**
        @brief GUI_button
        construction no1 de Button
        @param rendu (rendu affichage)
        @param nom: champs nom du button
        @param pathfont: chemin d'acces au font
        @param (x,y) : position du Button
        @param direction : directio  du Texte dans le button(CENTER,LEFT,RIGHT)=>LEFT
        @param style : style de Texte(gras,italique..) => normal
        @param w,h: longeur /largeur du Button
    */
    GUI_button(SDL_Renderer *rendu,std::string nom,std::string pathfont,int tsize,int x,int y,int direction=Widget::LEFT,int style=TTF_STYLE_NORMAL,int w=100,int h=30):GUI_Shape(x,y,w,h){

        this->ID=W_BUTTON;
        btn_name=new GUI_Texte(rendu,pathfont,x,y,nom,tsize,style);
        this->directionRender=direction;
        btn_name->setWithHeightRender(w,h,direction);
        gRenderCpy=rendu;
    }
    /**
        @brief GUI_button
        construction no2 de Button
        @param rendu (rendu affichage)
        @param cptext: Texture du texte
        @param (x,y) : position du Button
        @param direction : directio  du Texte dans le button(CENTER,LEFT,RIGHT)=>LEFT
        @param style : style de Texte(gras,italique..) => normal
        @param w,h: longeur /largeur du Button
    */
    GUI_button(SDL_Renderer *rendu,SDL_Texture *cptext,int x,int y,int direction=Widget::LEFT,int w=100,int h=30):GUI_Shape(x,y,w,h){

        this->ID=W_BUTTON;

        btn_name=new GUI_Texte(rendu,cptext,x,y);

        this->directionRender=direction;

        btn_name->setWithHeightRender(w,h,direction);
    }

    /**
        @brief GUI_button
        construction no3 de Button
        @param btn : button de copy
    */
    GUI_button(GUI_button *btn):GUI_Shape(btn->getRect().x,btn->getRect().y,btn->getRect().w,btn->getRect().h){
        this->ID=W_BUTTON;

        btn_name=btn->getTextButton();
    }

    /**
        @brief GUI_button
        construction no4 de Button
        @param rendu (rendu affichage)
        @param (x,y) : position du Button
        @param w,h: longeur /largeur du Button
    */
    GUI_button(SDL_Renderer *rendu,int x,int y,int w=100,int h=30,int directionRender=Widget::CENTER):GUI_Shape(x,y,w,h){
        this->ID=W_BUTTON;
        this->directionRender=directionRender;
        gRenderCpy=rendu;
    }

    /**
        @brief GUI_button
        construction no1 de Button
        @param rendu (rendu affichage)
        @param nom: champs nom du button
        @param font: font a charger
        @param (x,y) : position du Button
        @param direction : directio  du Texte dans le button(CENTER,LEFT,RIGHT)=>LEFT
        @param style : style de Texte(gras,italique..) => normal
        @param w,h: longeur /largeur du Button
    */
    GUI_button(SDL_Renderer *rendu,std::string nom,TTF_Font *font,int x,int y,int direction=Widget::LEFT,int w=100,int h=30):GUI_Shape(x,y,w,h){

        this->ID=W_BUTTON;
        btn_name=new GUI_Texte(rendu,font,x,y,nom);
        this->directionRender=direction;
        btn_name->setWithHeightRender(w,h,direction);
        gRenderCpy=rendu;
    }

    void Update(SDL_Renderer *rendu,SDL_Event &e)override{
        if(btn_name->getTexture()!=nullptr){
            btn_name->show(rendu,e);
        }
        if(icone!=nullptr){
            icone->show(rendu,e);
        }
    }

    GUI_Texte* getTextButton(){
        return btn_name;
    }

    void setText(SDL_Texture *texture){

    }
    void updateIconInButton(int directionIcon,GUI_Texture *ig){
        int spaceIcon=ICONBUTTONSIZE+20;
        switch(directionIcon){
            case LEFT:
                ig->setPosition(getRect().x,getRect().y);
                ig->setWithHeightRender(spaceIcon,getRect().h,Widget::CENTER);
            break;
            case RIGHT:

                ig->setPosition(getRect().x+getRect().w-spaceIcon,getRect().y);
                ig->setWithHeightRender(spaceIcon,getRect().h,Widget::CENTER);
            break;
        }
        //listIcon.push_back(std::unique_ptr<GUI_Image>(ig));
    }

    ///Changement Largeur/Hauteur Buton
    void setWithHeightRender(int w, int h, int direction)override{
        Widget::setWithHeightRender(w,h,direction);
        UpdateText();
    }

    void setPosition(int x,int y,int time=0,int vel=2)override{
        Widget::setPosition(x,y,time,vel);
        UpdateText();
    }

    void setTargetPosition(int x,int y)override
    {
        Widget::setTargetPosition(x,y);
        if(btn_name!=NULL)btn_name->setTargetPosition(x,y);
    }

    ///fonction Changer la position du texte dans le Button
    void UpdateText(){
        if(btn_name!=NULL)btn_name->setPosition(getRect().x,getRect().y);
        if(btn_name!=NULL)btn_name->setWithHeightRender(getRect().w,getRect().h,directionRender);
    }

    void AddIcon(std::string pathhIcon,int direction=Widget::LEFT){
        icone=new GUI_Image(gRenderCpy,pathhIcon,0,0);
        icone->resize(getRect().h-10,getRect().h-10);
        switch(direction){
        case LEFT:
            if(btn_name!=NULL){
                icone->setPosition(btn_name->getRect().x-5,getRect().y+getRect().h/2-icone->getRect().h/2);
                btn_name->setPosition(icone->getRect().x+icone->getRect().w+5,btn_name->getRect().y);
            }
            break;
        case RIGHT:
            if(btn_name!=NULL){
                icone->setPosition(getRect().x+getRect().w-icone->getRect().w-10,getRect().y+getRect().h/2-icone->getRect().h/2);
            }
            break;
        }
    }
};
#endif // GUI_BUTTON_H_INCLUDED
