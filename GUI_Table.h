#ifndef GUI_TABLE_H_INCLUDED
#define GUI_TABLE_H_INCLUDED
#define SIZEBUTTONOVERFLOW 25
struct Ceil{
    Widget *widget;
    int ID;
};
struct Header{
    GUI_button *btn;
    int ID;
    std::vector<Ceil>cell;
};
class GUI_Table:public BorderTexture{
private:

    std::vector<Header> listHeader;

    BorderTexture *plan;

    TTF_Font *font;

    bool overflowShow=true;

    GUI_button *btnUp;

    GUI_button *btnDwn;

    GUI_svg *arrow;

    int topPosition=0;
public:
    GUI_Table(SDL_Renderer *rendu,int x,int y,int w,int h):BorderTexture(rendu,x,y,w,h){
        plan=new BorderTexture(rendu,0,0,w,h);
        gRenderCpy=rendu;

        arrow=new GUI_svg(rendu,0,0);

        arrow->DrawTriangle(SIZEBUTTONOVERFLOW/2,SIZEBUTTONOVERFLOW/2,1,"#fff",true,"#fff");

        btnUp=new GUI_button(rendu,"u","font.ttf",0,0,CENTER,TTF_STYLE_NORMAL,SIZEBUTTONOVERFLOW,SIZEBUTTONOVERFLOW);
        btnUp->setPosition(x+w+5,y+h/2-SIZEBUTTONOVERFLOW+1);
        btnUp->getTextButton()->setTexture(arrow->getTexture());
        btnUp->getTextButton()->setPosition(btnUp->getRect().x,btnUp->getRect().y);
        btnUp->getTextButton()->setWithHeightRender(btnUp->getRect().w,btnUp->getRect().h,Widget::CENTER);

        btnDwn=new GUI_button(rendu,"u","font.ttf",0,0,CENTER,TTF_STYLE_NORMAL,SIZEBUTTONOVERFLOW,SIZEBUTTONOVERFLOW);
        btnDwn->setPosition(btnUp->getRect().x,btnUp->getRect().y+btnUp->getRect().h-1);
        btnDwn->getTextButton()->setTexture(arrow->getTexture());
        btnDwn->getTextButton()->setPosition(btnDwn->getRect().x,btnDwn->getRect().y);
        btnDwn->getTextButton()->rotateFlip(180);
        btnDwn->getTextButton()->setWithHeightRender(btnDwn->getRect().w,btnDwn->getRect().h,Widget::CENTER);

        btnUp->setTimeToClicks(50);
        btnDwn->setTimeToClicks(50);

    }
    ~GUI_Table(){
        delete plan;
        for(int i=0;i<listHeader.size();i++){
            delete listHeader[i].btn;
            for(int j=0;j<listHeader[i].cell.size();j++){
                delete listHeader[i].cell[j].widget;
            }
            listHeader[i].cell.clear();
        }
        listHeader.clear();

    }
    /**
    */
    GUI_button *getHeader(int id){
        return listHeader[id].btn;
    }

    /**

    */
    void AddHeader(std::string elt,std::string pathfont,int tsize,int style=TTF_STYLE_NORMAL,int direction=Widget::LEFT){
        Header l;
        l.btn=new GUI_button(gRenderCpy,elt.c_str(),pathfont,tsize,0,0,direction,style,getRect().w,40);
        //=====
        l.ID=listHeader.size();
        //=====
        l.btn->setTargetPosition(getRect().x,getRect().y);
        listHeader.push_back(l);
        //=====
        if(listHeader.size()==1){
            topPosition=listHeader[0].btn->getRect().h-1;
            plan->setPosition(0,listHeader[0].btn->getRect().h-1);
        }
        CheckHeaderPosition();
    }

    /**

    */
    void CheckHeaderPosition(){
        int k=listHeader.size();
        int p=0;
        int tsize=getRect().w;
        for(int i=0;i<listHeader.size();i++){
            p=tsize/((k-i)>0?k-i:1);
            if(k>0){
                listHeader[i].btn->resizeShape(p,listHeader[i].btn->getRect().h);
            }
            if(i==0){
                listHeader[i].btn->setPosition(0,0);
            }else{
                listHeader[i].btn->setPosition(listHeader[i-1].btn->getRect().x+listHeader[i-1].btn->getRect().w-1,0);
            }
            tsize=tsize-p+1;
        }
    }

    /*void AddCeil(int iHeader,std::string elt,std::string pathfont,int tsize,int style=TTF_STYLE_NORMAL,int direction=Widget::LEFT){
        Ceil l;
        l.widget=new GUI_button(gRenderCpy,elt.c_str(),pathfont,tsize,listHeader[iHeader].btn->getRect().x,listCeil.size()>0?listCeil[listCeil.size()-1].widget->getRect().y+listCeil[listCeil.size()-1].widget->getRect().h-1:0,direction,style,getRect().w,40);
        l.ID=listCeil.size();
        listCeil.push_back(l);
    }*/

    /**

    */
    void AddCeil(int iHeader,Widget* tmp){
        Ceil l;
        int tcellSize=listHeader[iHeader].cell.size();
        l.widget=tmp;
        if(tcellSize==0){
            l.widget->setPosition(listHeader[iHeader].btn->getRect().x,0);
        }else{
            l.widget->setPosition(listHeader[iHeader].btn->getRect().x,listHeader[iHeader].cell[tcellSize-1].widget->getRect().y+listHeader[iHeader].cell[tcellSize-1].widget->getRect().h-1);
        }
        l.widget->resizeShape(listHeader[iHeader].btn->getRect().w,-1);
        l.widget->setTargetPosition(getRect().x,plan->getRect().y+getRect().y);

        l.ID=tcellSize+iHeader;
        l.widget->setCheckVisibiliy(getHeader(iHeader)->getTextButton()->getCheckVisibiliy());
        listHeader[iHeader].cell.push_back(l);
        UpdateShapePlan();
    }

    /**
    */
    void deleteCeil(int iHeader,int iCeil){
        delete listHeader[iHeader].cell[iCeil].widget;
        listHeader[iHeader].cell[iCeil].widget=NULL;
        listHeader[iHeader].cell.pop_back();
    }

    /**

    */
    void DropLineTable(int line){
        int ypos=0;
        int xpos=0;
        int sizeCeil=listHeader[0].cell.size();
        for(int i=0;i<listHeader.size()&&sizeCeil>=1;i++){
            if(sizeCeil>1){
                xpos=listHeader[i].cell[line].widget->getRect().x;
                ypos=listHeader[i].cell[line].widget->getRect().y;
                listHeader[i].cell[line]=listHeader[i].cell[sizeCeil-1];
                listHeader[i].cell[sizeCeil-1].widget=NULL;
                deleteCeil(i,sizeCeil-1);
                listHeader[i].cell[line].widget->setPosition(xpos,ypos);
            }else{
                if(sizeCeil==1)deleteCeil(i,sizeCeil-1);
            }
            //updateListCeil();
        }
        UpdateShapePlan();
    }

    /**

    */
    void updateListCeil(){
        Ceil tmp;
         for(int i=0;i<listHeader.size();i++){
            for(int j=0;j<listHeader[i].cell.size();j++){
                tmp=listHeader[i].cell[j];
                listHeader[i].cell[j]=listHeader[i].cell[j+1];
                listHeader[i].cell[j+1]=tmp;
            }
         }
    }

    void StartToShow(SDL_Renderer* rendu, SDL_Event event){

        plan->setBorderColorState(-1,getBorderColor(Widget::BTN_STAT_NONE));

        btnUp->setFillColorState(-1,getFillColor(Widget::BTN_STAT_NONE));
        btnDwn->setFillColorState(-1,getFillColor(Widget::BTN_STAT_NONE));

        btnUp->setBorderColorState(-1,getBorderColor(Widget::BTN_STAT_NONE));
        btnDwn->setBorderColorState(-1,getBorderColor(Widget::BTN_STAT_NONE));

        plan->StartToShow(rendu,event);
            for(int i=0;i<listHeader.size();i++){
                for(int j=0;j<listHeader[i].cell.size();j++){
                    if(listHeader[i].cell[j].widget!=NULL){
                        listHeader[i].cell[j].widget->setTargetPosition(getRect().x,plan->getRect().y+getRect().y);
                        if(listHeader[i].btn->getTextButton()->getCheckVisibiliy()){
                            if(listHeader[i].btn->getTextButton()->isCheckIt()){
                                if(listHeader[i].cell[j].widget->getCheckVisibiliy()){
                                    listHeader[i].cell[j].widget->setCheckIt(!listHeader[i].cell[j].widget->isCheckIt());
                                }
                            }
                        }
                        listHeader[i].cell[j].widget->setBorderColorState(-1,getBorderColor(getCurrentState()));
                        listHeader[i].cell[j].widget->setFillColorState(-1,getFillColor(getCurrentState()));
                        listHeader[i].cell[j].widget->show(rendu,event,plan->getTexture());
                    }
                }
            }
        plan->EndToShow(rendu);
        BorderTexture::StartToShow(rendu,event);
            plan->show(rendu,event);
            for(int i=0;i<listHeader.size();i++){
                //=== [Header List] ====//
                listHeader[i].btn->setBorderColorState(-1,getBorderColor(getCurrentState()));
                listHeader[i].btn->setFillColorState(-1,getFillColor(getCurrentState()));
                listHeader[i].btn->show(rendu,event);
            }

    }

    /**

    */
    void UpdateShapePlan(){
        if(listHeader[0].cell.size()>0){
            SDL_Rect posCeilInit=listHeader[0].cell[listHeader[0].cell.size()-1].widget->getRect();
            int sizeHauteur=posCeilInit.y+posCeilInit.h-1+topPosition;
            if(sizeHauteur>getRect().h){
                overflowShow=true;
                plan->resizeShape(-1,sizeHauteur);
            }else{
                overflowShow=false;
            }
        }else{
            overflowShow=false;
        }
    }

    /**
    */
    void Update(SDL_Renderer* rendu, SDL_Event& e)override{
        StartToShow(rendu,e);
        EndToShow(rendu);
        if(overflowShow){
            if(btnUp->getCurrentState()==Widget::BTN_STAT_CLICKS){
                gotoDirection(Widget::UP,5);
            }
            if(btnDwn->getCurrentState()==Widget::BTN_STAT_CLICKS){
                gotoDirection(Widget::DOWN,5);
            }
            btnUp->show(rendu,e);
            btnDwn->show(rendu,e);
        }else{
            plan->setPosition(plan->getRect().x,topPosition);
        }
        if(plan->getRect().y+plan->getRect().h<getRect().h){
            plan->setPosition(plan->getRect().x,topPosition-abs(plan->getRect().h-getRect().h));
        }
    }

    /**
    */
    void gotoDirection(int direction,int vel){
        switch(direction){
            case Widget::UP:
                plan->setPosition(plan->getRect().x,topPosition,10,vel);
            break;

            case Widget::DOWN:
                plan->setPosition(plan->getRect().x,-abs(plan->getRect().h-getRect().h)+topPosition,10,vel);
            break;

            case Widget::LEFT:
                plan->setPosition(plan->getRect().x+vel,plan->getRect().y);
            break;

            case Widget::RIGHT:
                plan->setPosition(plan->getRect().x-vel,plan->getRect().y);
            break;
        }
    }
};


#endif // GUI_TABLE_H_INCLUDED
