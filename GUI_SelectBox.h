#ifndef GUI_SELECTBOX_H_INCLUDED
#define GUI_SELECTBOX_H_INCLUDED

#include"GUI_Button.h"
#include"GUI_BordererTexture.h"
#include"GUI_svg.h"

#define WIDTHZONEBOX 250
#define HEIGHTZONEBOX 1000

#define SELECTBUTTONHEIGHT 35
#define TIMETOCHECK 10

struct selectElement{
    GUI_button *btn;
    int ID;
};
class GUI_SelectBox:public GUI_button
{
private:

    ///Variable pour Afficher la liste des Options
    BorderTexture *zoneSelectElement;

    ///Fonction d'ouverture et fermeture Pop
    void CloseOpenPopUp(SDL_Event &event);

    ///Temps Animation ouverture/Fermeture
    Timer anim;

    int *id=0;

    int iselectionner=0;

    bool showList=false;

    SDL_Rect zoneList;

    std::vector<selectElement> listBtn;

    SDL_Color white={255,255,255,255};

    TTF_Font *ftcpy;

    bool Ischange=true;

    GUI_svg *arrow;

    SDL_Rect borderArrow;
public:

    /**
        @brief GUI_SelectBox
        construction de selectbox
        @param rendu (rendu affichage)
        @param x,y : position du select
        @param w,h: longeur /largeur du selectbutton
        @param directionRender: direction du render
        @param hselect: longeur /largeur du selectzone
    */
    GUI_SelectBox(SDL_Renderer *rendu,int *data,int x,int y,TTF_Font *ft,int w=100,int h=30,int directionRender=Widget::LEFT):GUI_button(rendu,x,y,w,h,directionRender){
        this->ID=W_SELECT_BOX;
        id=data;
        arrow=new GUI_svg(rendu,x,y);
        arrow->DrawTriangle(ICONBUTTONSIZE,ICONBUTTONSIZE,1,"#fff",true,"#fff");
        this->directionRender=directionRender;
        zoneSelectElement=new BorderTexture(rendu,getRect().x,getRect().y+getRect().h,getRect().w,1,false,true);
        ftcpy=ft;
        gRenderCpy=rendu;
        arrow->rotateFlip(180);
        updateIconInButton(RIGHT,arrow);
    }


    ///Destructeur de Select Box
    ~GUI_SelectBox(){
        TTF_CloseFont(ftcpy);
        delete zoneSelectElement;
        deleteListButton();
        delete arrow;
    }

    /**
        @brief deleteListButton
        liberation de l'espace
    */
    void deleteListButton(){
        for(int i=listBtn.size()-1;i>0;i--){
            delete listBtn[i].btn;
            listBtn.pop_back();
        }
        listBtn.clear();
    }

    void setWithHeightRender(int w, int h, int direction)override{

        Widget::setWithHeightRender(w,h,direction);
        zoneSelectElement->setPosition(getRect().x,getRect().y+getRect().h-1);
        updateIconInButton(RIGHT,arrow);

    }

    void setPosition(int x,int y,int time=0,int vel=2)override{

        Widget::setPosition(x,y,time,vel);
        zoneSelectElement->setPosition(getRect().x,getRect().y+getRect().h-1);
        updateIconInButton(RIGHT,arrow);

        if(btn_name!=nullptr){
            btn_name->setPosition(getRect().x,getRect().y);
            btn_name->setWithHeightRender(getRect().w-(ICONBUTTONSIZE+20),getRect().h,directionRender);
        }
    }

    void setBorderColorState(int state, SDL_Color col)override{
        Widget::setBorderColorState(state,col);
        zoneSelectElement->setBorderColorState(state,col);
        arrow->setColor(col);
    }

    void Update(SDL_Renderer *rendu,SDL_Event &e)override{
        if(getCurrentState()==Widget::BTN_STAT_CLICKS){
             if(anim.attendre(20))showList=!showList;
        }else{
            if(OnGlobalMouseClicks(e)&&getCurrentState()!=Widget::BTN_STAT_HOVER&&showList){
                showList=false;
            }
        }
        drawSelectElement(rendu,e);

        //=== Changement du button seleon element selectionner ====
        if(Ischange){
            if(btn_name!=nullptr){
                btn_name=nullptr;
                delete btn_name;
            }
            btn_name=new GUI_Texte(gRenderCpy,listBtn[iselectionner].btn->getTextButton()->getTexture(),gRect.x,gRect.y);
            btn_name->setWithHeightRender(getRect().w-(ICONBUTTONSIZE+20),getRect().h,directionRender);
            Ischange=false;
        }
        if(btn_name!=nullptr){
            btn_name->show(rendu,e);
        }
        arrow->show(rendu,e);
        //====
        borderArrow=getRect();
        borderArrow.x=getRect().x+getRect().w-(ICONBUTTONSIZE+20);
        borderArrow.w=(ICONBUTTONSIZE+20);

        //=========
        DrawRenderColor(rendu,gBorderColor);
        SDL_RenderDrawRect(rendu,&borderArrow);
        //==========

        zoneSelectElement->show(rendu,e,false);
        if(showList){
            zoneSelectElement->OpenBorderTexture();
        }else{
            zoneSelectElement->CloseBorderTexture();
        }
    }

    /**
        @brief drawSelectElement
        dessin a l'interieure du zoneselect
    */
    void drawSelectElement(SDL_Renderer *rendu,SDL_Event &e){
        zoneSelectElement->StartToShow(rendu,e);
            for(int i=0;i<listBtn.size();i++){
                listBtn[i].btn->setTargetPosition(zoneSelectElement->getRect().x,zoneSelectElement->getRect().y);
                if(listBtn[i].btn->getCurrentState()==Widget::BTN_STAT_CLICKS&&zoneSelectElement->IsCheckMouseEvent()){
                    iselectionner=i;
                    *id=listBtn[i].ID;
                    Ischange=true;
                }
                listBtn[i].btn->setBorderColorState(-1,gBorderColor);
                listBtn[i].btn->show(rendu,e,zoneSelectElement->getTexture());
            }
        zoneSelectElement->EndToShow(rendu);

    }

    /**
        @brief AddSelectItem
        ajouter des element dans le select
        @param btn:boutton de selection
        @param id:identifiant de selection
    */
    void AddSelectItem(std::string name,int id=ERROR){
        GUI_button *btn=new GUI_button(gRenderCpy,name,ftcpy,0,0,Widget::LEFT,getRect().w,getRect().h-10);
        selectElement tmp;
        if(id==ERROR){
            tmp.ID=listBtn.size();
        }else{
            tmp.ID=id;
        }
        tmp.btn=btn;
        if(listBtn.size()==0){
            tmp.btn->setPosition(0,0);
        }else{
            tmp.btn->setPosition(0,listBtn[listBtn.size()-1].btn->getRect().y+listBtn[listBtn.size()-1].btn->getRect().h-1);
        }
        tmp.btn->setTargetPosition(zoneSelectElement->getRect().x,zoneSelectElement->getRect().y);
        tmp.btn->setFillColorState(-1,white);
        listBtn.push_back(tmp);
        zoneSelectElement->setHeight(listBtn[0].btn->getRect().y+listBtn[listBtn.size()-1].btn->getRect().y+listBtn[listBtn.size()-1].btn->getRect().h-1);
    }

    /**
        @brief AddSelectItem
        Obtenir les Indices des element selectionner
        @param btn:boutton de selection
        @param id:identifiant de selection
    */
    int getValue(){
        return *id;
    }

    /**
        @brief SetDefaultWithId
        deffinir l'element selectionner par defaut
        @param id:identifiant de selection
    */
    void SetDefaultWithId(int ID){

    }

};

#endif // GUI_SELECTBOX_H_INCLUDED
