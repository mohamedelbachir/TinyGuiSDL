#ifndef GUI_PANEL_H_INCLUDED
#define GUI_PANEL_H_INCLUDED
#include<memory>
struct idWidget{
    Widget *widget;
    int id;
};
class GUI_Panel:public GUI_button{
protected :

    ///booleen d'affichage du panel
    bool showList=false;

    ///definition des temps animations
    Timer anim;

    ///panelborduretexture
    BorderTexture *panel;

    ///zone de list
    SDL_Rect zoneList;

    bool panelHover=false;

    std::vector<idWidget>listWidget;
public:

    /**
        @brief GUI_Panel
        construction de panel
        @param rendu (rendu affichage)
        @param t : button de refference au panel
        @param w,h: longeur /largeur du Button
    */
    GUI_Panel(SDL_Renderer *rendu,GUI_button *t,int w,int h,int direction=Widget::LEFT):GUI_button(t){
        this->ID=W_PANEL;
        panel=new BorderTexture(rendu,t->getRect().x+t->getRect().w/2-w/2,t->getRect().y+t->getRect().h+2,w,h,false,true);
        gRenderCpy=rendu;
        setParentRender(rendu);
    }

    /**
        @brief GUI_Panel
        construction de panel
        @param rendu (rendu affichage)
        @param t : button de refference au panel
        @param w,h: longeur /largeur du Button
        @param wpanel,hpanel: longeur /largeur du panel
    */
    GUI_Panel(SDL_Renderer *rendu,SDL_Texture *t,int x,int y,int w,int h,int Wpanel,int Hpanel,int direction=Widget::LEFT):GUI_button(rendu,t,x,y,direction,w,h){
        this->ID=W_PANEL;
        panel=new BorderTexture(rendu,x+w/2-Wpanel/2,y+h+2,Wpanel,Hpanel,false,true);
        gRenderCpy=rendu;
    }

    BorderTexture *getPanel(){
        return panel;
    }

    void setBorderColorState(int state, SDL_Color col)override{
        Widget::setBorderColorState(state,col);
        panel->setBorderColorState(state,col);
    }


    void Update(SDL_Renderer* rendu, SDL_Event& e)override{
        GUI_button::Update(rendu,e);
        panel->StartToShow(rendu,e);
            for(int i=0;i<listWidget.size();i++){
                listWidget[i].widget->setBorderColorState(getCurrentState(),getBorderColor(getCurrentState()));
                listWidget[i].widget->setFillColorState(getCurrentState(),getFillColor(getCurrentState()));
                listWidget[i].widget->SetCheckMouseEvent(showList);
                listWidget[i].widget->show(rendu,e,panel->getTexture());
            }
        panel->EndToShow(rendu);

        if(getCurrentState()==Widget::BTN_STAT_CLICKS){
             if(anim.attendre(20)){
                    showList=!showList;
             }
        }else{
            if(OnGlobalMouseClicks(e)&&getCurrentState()!=Widget::BTN_STAT_HOVER&&showList){
                showList=false;
            }
        }

        panel->show(rendu,e);
        if(showList){
            panel->OpenBorderTexture();
        }else{
            panel->CloseBorderTexture();
        }
    }
    bool isOpen(){
        return showList;
    }

    void setShowList(bool enable){
        showList=enable;
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

        panel->setHeight(listWidget[0].widget->getRect().y+listWidget[listWidget.size()-1].widget->getRect().y+listWidget[listWidget.size()-1].widget->getRect().h);

    }
    Widget *getElement(int id){
        bool found=false;
        int i=0;
        Widget *result=nullptr;
        if(listWidget.size()>0){
            while(!found&&i<listWidget.size()){
                if(listWidget[i].id==id){
                    found=true;
                    break;
                }
                i++;
            }
        }
        if(found){
            result=listWidget[i].widget;
        }
        return result;
    }
};
#endif // GUI_PANEL_H_INCLUDED
