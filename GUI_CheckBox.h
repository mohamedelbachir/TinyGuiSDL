#ifndef GUI_CHECKBOX_H_INCLUDED
#define GUI_CHECKBOX_H_INCLUDED
#include "GUI_Shape.h"
class GUI_CheckBox{
protected:
    GUI_Shape inRect;
    GUI_Shape boxRect;
    bool isVisble=false;
    SDL_Color white={255,255,255,255};
    SDL_Color black={0,0,0,255};
    bool checkIt=false;
    bool once=false;
    bool checkWithLabel=true;
public:
    //static bool doOnce=false;
    GUI_CheckBox(){
        boxRect=GUI_Shape(0,0,SIZECHECKBOX,SIZECHECKBOX);
        boxRect.setFillColorState(-1,white);
        boxRect.setBorderColorState(-1,black);
        UpdateRect();
    }
    GUI_CheckBox(int x,int y,int w=SIZECHECKBOX,int h=SIZECHECKBOX){
        boxRect=GUI_Shape(x,y,w,h);
        boxRect.setFillColorState(-1,white);
        boxRect.setBorderColorState(-1,black);
        UpdateRect();
    }
    GUI_Shape* getBoxCheck(){
        return &boxRect;
    }
    void showCheck(bool enable){
        isVisble=enable;
    }

    void setCheckState(bool check){
        checkIt=check;
    }
    bool getCheckState(){
        return checkIt;
    }
    void setCheckWithLabel(bool enable){
        checkWithLabel=enable;
    }
    void UpdateRect(){
        inRect.setPosition(boxRect.getRect().x+boxRect.getRect().w/4,boxRect.getRect().y+boxRect.getRect().h/4);
        inRect.resizeShape(boxRect.getRect().w/2,boxRect.getRect().h/2);
        inRect.setFillColorState(-1,boxRect.getBorderColor(Widget::BTN_STAT_NONE));
        inRect.setBorderColorState(-1,boxRect.getBorderColor(Widget::BTN_STAT_NONE));
    }
    virtual void setcheckBoxPosition(GUI_CheckBox *bx){}
    void showCheck(SDL_Renderer *rendu,SDL_Event &e,Widget *t){
        if(!once){
            boxRect.setPosition(t->getRefRect()->x,t->getRefRect()->y);
        }else{
            boxRect.setPosition(t->getRefRect()->x-boxRect.getRect().w-3,boxRect.getRect().y);
        }
        setcheckBoxPosition(this);
        UpdateRect();
        boxRect.setTargetPosition(t->getGlobalTargetPosition().x,t->getGlobalTargetPosition().y);
        boxRect.show(rendu,e);
        if(!once){
            once=true;
            checkIt=t->isCheckIt();
        }
        if(boxRect.getCurrentState()==Widget::BTN_STAT_CLICKS||(t->getCurrentState()==Widget::BTN_STAT_CLICKS&&checkWithLabel)){
            checkIt=!checkIt;
            t->setCheckIt(checkIt);
        }
        if(t->isCheckIt()){
            inRect.show(rendu,e);
        }
    }

};


#endif // GUI_CHECKBOX_H_INCLUDED
