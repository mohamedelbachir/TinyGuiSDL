#ifndef GUI_RADIOBUTTON_H_INCLUDED
#define GUI_RADIOBUTTON_H_INCLUDED
#include"GUI_svg.h"

#define SIZEICONRADIO 10
struct radioElement{
    GUI_Texte *texte;
    int ID;
    GUI_Image *imgRadio;
};

class GUI_radioButton:public GUI_Texture{
private:

    ///Identifiant des Elements du radio selectionner
    int *id;

    /**Texture de representation de chaque etat iconRadio[default,click,hover] */
    SDL_Texture* stateRadio[numberState];

    /**liste des radioelement*/
    std::vector<radioElement> radioelt;

    GUI_svg *icDefault;

    GUI_svg *icHover;

    GUI_svg *icClicks;

public:

    /**
       @brief GUI_radioButton
       constructeur radiobutton
       @param   - rendu     : Rendu Affichage de la radioButton
       @param   - identifier: variable obtenenant ID de elemeent ardio
    **/
    GUI_radioButton(SDL_Renderer *rendu,int *data){

        this->ID=W_RADIO;
        id=data;
        /*direction de l'icone*/
        directionRender=LEFT;

        icDefault=new GUI_svg(rendu,0,0);
        icHover=new GUI_svg(rendu,0,0);
        icClicks=new GUI_svg(rendu,0,0);

        /*chargement des icones Radio*/
        icDefault->DrawCircle(SIZEICONRADIO,1,"#000");
        stateRadio[Widget::BTN_STAT_NONE]=icDefault->getTexture();

        //======
        icDefault->DrawCircle(SIZEICONRADIO,1,"#000");
        stateRadio[Widget::BTN_STAT_HOVER]=icDefault->getTexture();

        //======
        icDefault->DrawDoubleCircle(SIZEICONRADIO,SIZEICONRADIO/2,1,1,false,true);
        stateRadio[Widget::BTN_STAT_CLICKS]=icDefault->getTexture();

        SetDisplay(false);

        //======

        SDL_QueryTexture(stateRadio[Widget::BTN_STAT_NONE],NULL,NULL,&gRect.w,&gRect.h);
        //UpdateSizeTexture();
    }

    ~GUI_radioButton(){
        if(icDefault!=nullptr){
            delete icDefault;
        }
        if(icHover!=nullptr){
            delete icHover;
        }if(icClicks!=nullptr){
            delete icClicks;
        }
        for(int i=0;i<radioelt.size();i++){
            if(radioelt[i].imgRadio!=nullptr){
                delete radioelt[i].imgRadio;
            }
            if(radioelt[i].texte!=nullptr){
                delete radioelt[i].texte;
            }
        }
        radioelt.clear();
    }
    /**
        @brief addRadioElement
        *   ajout des radio element
        *   @param   - t  : texte de radio
        *   @param   - ID : variable obtenenant ID de element ardio
    **/
    void addRadioElement(GUI_Texte *t,int ID=ERROR){

        radioElement tmp;

        tmp.imgRadio=new GUI_Image(t->getRenderCopy(),stateRadio[Widget::BTN_STAT_NONE],t->getRect().x,t->getRect().y);

        t->setPosition(t->getRect().x+gRect.w+5,t->getRect().y+getRect().h/2-t->getRect().h/2+2);

        tmp.texte=t;

        if(ID==ERROR){
            tmp.ID=radioelt.size();
        }else{
            tmp.ID=ID;
        }

        radioelt.push_back(tmp);

        if(radioelt.size()==1){
            *id=ID;
        }
    }

    /**
    *   @brief setDefault
    *   ajout des radio element
    *   @param   - t  : texte de radio
    *   @param   - ID : variable obtenenant ID de elemeent ardio
    **/
    void setDefault(int ID){
        *id=ID;
    }

    void setBorderColorState(int state, SDL_Color col)override{

        icDefault->setBorderColorState(state,col);
        //stateRadio[Widget::BTN_STAT_NONE]=icDefault->getTexture();

        icHover->setBorderColorState(state,col);
        //stateRadio[Widget::BTN_STAT_HOVER]=icHover->getTexture();

        icClicks->setBorderColorState(state,col);
        //stateRadio[Widget::BTN_STAT_CLICKS]=icClicks->getTexture();

    }
    int findRadioElementWithId(int id){
        int i=0;
        if(radioelt.size()>0){
            while(radioelt[i].ID!=id){
                i++;
            }
        }
        return i;
    }
    SDL_Rect getRadioRect(int id){
        int i=findRadioElementWithId(id);
        SDL_Rect tmp;
        tmp.x=radioelt[i].imgRadio->getRect().x;
        tmp.y=radioelt[i].imgRadio->getRect().y;
        tmp.h=radioelt[i].imgRadio->getRect().h;
        tmp.w=radioelt[i].imgRadio->getRect().w+5+radioelt[i].texte->getRect().w;
        return tmp;
    }

    void setElementRadioPosition(int id,int x,int y){
        int k=findRadioElementWithId(id);
        radioelt[k].imgRadio->setPosition(x,y);
        radioelt[k].texte->setPosition(x+radioelt[k].imgRadio->getRect().w+5,y+radioelt[k].imgRadio->getRect().h/2-radioelt[k].texte->getRect().h/2+2);
    }
    void setPosition(int x,int y,int time=0){
        Widget::setPosition(x,y,time);
        for(int i=0;i<radioelt.size();i++){
            setElementRadioPosition(radioelt[i].ID,getRadioRect(radioelt[i].ID).x+getRect().x,getRadioRect(radioelt[i].ID).y+getRect().y);
        }
    }
    void Update(SDL_Renderer *rendu,SDL_Event &e)override{

        for(int i=0;i<radioelt.size();i++){

           /*Clicks radioButton*/
           if(radioelt[i].texte->getCurrentState()==Widget::BTN_STAT_CLICKS||radioelt[i].imgRadio->getCurrentState()==Widget::BTN_STAT_CLICKS){
                setDefault(radioelt[i].ID);
           }else{
                /*Hover radioButton*/
               if(radioelt[i].texte->getCurrentState()==Widget::BTN_STAT_HOVER||radioelt[i].imgRadio->getCurrentState()==Widget::BTN_STAT_HOVER){
                   if(radioelt[i].ID!=*id){
                        radioelt[i].imgRadio->setTexture(stateRadio[Widget::BTN_STAT_HOVER]);
                   }
               }else{

                   /*default radioButton*/
                   if(radioelt[i].ID!=*id){
                     radioelt[i].imgRadio->setTexture(stateRadio[Widget::BTN_STAT_NONE]);
                   }
               }
           }

           /*Element selectionner*/
           if(radioelt[i].ID==*id){
               radioelt[i].imgRadio->setTexture(stateRadio[Widget::BTN_STAT_CLICKS]);
           }
        }

    }
    void setTargetPosition(int x, int y)override{
        for(int i=0;i<radioelt.size();i++){
            radioelt[i].texte->setTargetPosition(x,radioelt[i].texte->getRect().y-y);
            radioelt[i].imgRadio->setTargetPosition(x,radioelt[i].imgRadio->getRect().y-y);
        }
    }
    void show(SDL_Renderer* rendu, SDL_Event& e, SDL_Texture* dtest)override{
        Update(rendu,e);
        for(int i=0;i<radioelt.size();i++){
            radioelt[i].texte->show(rendu,e,dtest);
            radioelt[i].imgRadio->show(rendu,e,dtest);
        }
    }

};


#endif // GUI_RADIOBUTTON_H_INCLUDED
