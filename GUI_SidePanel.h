#ifndef GUI_SIDEPANEL_H_INCLUDED
#define GUI_SIDEPANEL_H_INCLUDED

class GUI_SidePanel:public GUI_button{
private:

    ///Variable pour Afficher la liste des Widgets
    BorderTexture *panel;

    ///Temps Animation ouverture/Fermeture
    Timer anim;

    std::vector<idWidget> listWidget;

    SDL_Color white={255,255,255,255};

    TTF_Font *ftcpy;

    GUI_svg *arrow;

    SDL_Rect borderArrow;

    bool showList=false;
 public:

    GUI_SidePanel(SDL_Renderer *rendu,std::string nom,std::string pathfont,int tsize,int x,int y,int direction=Widget::LEFT,int style=TTF_STYLE_NORMAL,int w=100,int h=30):GUI_button(rendu,nom,pathfont,tsize,x,y,direction,style){
        this->ID=W_PANEL;
        arrow=new GUI_svg(rendu,x,y);
        arrow->DrawTriangle(ICONBUTTONSIZE,ICONBUTTONSIZE,1,"#fff",true,"#fff");
        this->directionRender=directionRender;
        panel=new BorderTexture(rendu,getRect().x-getRect().w,getRect().y+getRect().h,getRect().w,100);
        gRenderCpy=rendu;
        arrow->rotateFlip(90);
    }
    void setWithHeightRender(int w, int h, int direction)override{

        Widget::setWithHeightRender(w,h,direction);
        panel->setPosition(getRect().x,getRect().y+getRect().h-1);
        updateIconInButton(RIGHT,arrow);

    }

    void setPosition(int x,int y,int time=0,int vel=2)override{

        Widget::setPosition(x,y,time,vel);
        panel->setPosition(getRect().x,getRect().y+getRect().h-1);
        updateIconInButton(RIGHT,arrow);

        if(btn_name!=nullptr){
            btn_name->setPosition(getRect().x,getRect().y);
            btn_name->setWithHeightRender(getRect().w-(ICONBUTTONSIZE+20),getRect().h,directionRender);
        }
    }

    void setBorderColorState(int state, SDL_Color col)override{
        Widget::setBorderColorState(state,col);
        panel->setBorderColorState(state,col);
        arrow->setColor(col);
    }

    void Update(SDL_Renderer *rendu,SDL_Event &e)override{

        if(btn_name!=nullptr){
            btn_name->show(rendu,e);
        }
        arrow->show(rendu,e);

        //=====
        borderArrow=getRect();
        borderArrow.x=getRect().x+getRect().w-(ICONBUTTONSIZE+20);
        borderArrow.w=(ICONBUTTONSIZE+20);

        //=========
        DrawRenderColor(rendu,gBorderColor);
        SDL_RenderDrawRect(rendu,&borderArrow);

        //==========

        panel->setPosition(getRealRect().x-panel->getRect().w+5,getRealRect().y);

    }
    void show(SDL_Renderer* rendu, SDL_Event& e, SDL_Texture* dtest=NULL)override{
        GUI_button::show(rendu,e,dtest);
        showList=getCurrentState()==BTN_STAT_HOVER||panel->getCurrentState()==BTN_STAT_HOVER;
        if(SDL_RenderTargetSupported(rendu)==SDL_TRUE){
           if(dtest!=NULL){
                SDL_SetRenderTarget(rendu,NULL);
           }
           panel->setFillColorState(-1,white);
           panel->setBorderColorState(-1,getBorderColor(BTN_STAT_NONE));
           panel->StartToShow(rendu,e);
                //list des element
                for(int i=0;i<listWidget.size();i++){
                    listWidget[i].widget->setBorderColorState(getCurrentState(),getBorderColor(getCurrentState()));
                    listWidget[i].widget->setFillColorState(getCurrentState(),getFillColor(getCurrentState()));
                    listWidget[i].widget->SetCheckMouseEvent(showList);
                    listWidget[i].widget->SetDisplay(showList);
                    listWidget[i].widget->show(rendu,e,panel->getTexture());
                }

           panel->EndToShow(rendu);
           if(showList){
                panel->show(rendu,e);
           }
           if(dtest!=NULL){
                SDL_SetRenderTarget(rendu,dtest);
           }
        }
    }
    void AddWidget(Widget *w,int id=-1){
        idWidget tmp;
        if(id==-1){
            id=listWidget.size();
        }else{
            tmp.id=id;
        }
        w->resizeShape(panel->getRect().w);
        if(listWidget.size()==0){
            w->setPosition(0,0);
        }else{
            w->setPosition(0,listWidget[listWidget.size()-1].widget->getRect().y+listWidget[listWidget.size()-1].widget->getRect().h-1);
        }
        w->setTargetPosition(panel->getRect().x,panel->getRect().y);
        tmp.widget=w;
        tmp.id=id;
        listWidget.push_back(tmp);

        //panel->setHeight(listWidget[0].widget->getRect().y+listWidget[listWidget.size()-1].widget->getRect().y+listWidget[listWidget.size()-1].widget->getRect().h);

    }
};


#endif // GUI_SIDEPANEL_H_INCLUDED

