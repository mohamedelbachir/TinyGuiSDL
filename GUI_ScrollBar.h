#ifndef GUI_SCROLLBAR_H_INCLUDED
#define GUI_SCROLLBAR_H_INCLUDED
#define SPACEBAR 20

struct btnScroll{
    GUI_Shape scrollBtnVert;
    SDL_Rect posDst;
};
class GUI_Scroll:public GUI_Shape{
private:
    GUI_button *btnVerticalUp;
    GUI_button *btnVerticalDown;

    GUI_svg *arrow;
    SDL_Rect  *srcRect;
    SDL_Rect  *dstRect;

    bool hasVertical=false;

    int velocity=2;

    SDL_Rect oldRect;

    btnScroll btn_vertical;

    SDL_Color col={255,0,0,255};

    int velocityX,velocityY;

private:

    void UpdateScroll(){
        int maxHeight=abs(srcRect->h-2*btnVerticalUp->getRect().h);
        int sizeVscroll=abs(dstRect->h-maxHeight);

        //===== [Cas de scroll Vertical] =======
        if(sizeVscroll<maxHeight){
            btn_vertical.scrollBtnVert.resizeShape(-1,maxHeight-sizeVscroll);
        }else{
            btn_vertical.scrollBtnVert.resizeShape(-1,SPACEBAR);
        }
        int distanceToReach=maxHeight-2*btn_vertical.scrollBtnVert.getRect().h;
        int distanceHidden=dstRect->h-srcRect->h;
        velocity=distanceHidden/distanceToReach;
        if(oldRect.y+dstRect->h>srcRect->h){
            hasVertical=true;
        }else{
            hasVertical=false;
        }
    }
public:
    GUI_Scroll(SDL_Renderer *rendu,SDL_Rect *src,SDL_Rect *dst):GUI_Shape(src->x+src->w-SPACEBAR,src->y,SPACEBAR,src->h){

        //CopyAdreesse source et element debordant
        srcRect=src;
        dstRect=dst;

        oldRect.x=dstRect->x;
        oldRect.y=dstRect->y;
        oldRect.w=dstRect->w;
        oldRect.h=dstRect->h;

        //=== Scroll Button
        btn_vertical.scrollBtnVert=GUI_Shape(0,0,SPACEBAR-4,0);
        btn_vertical.posDst=oldRect;
        //==== Definition Position pour le Premier element
        btn_vertical.scrollBtnVert.setPosition(getRect().x+getRect().w/2-btn_vertical.scrollBtnVert.getRect().w/2,getRect().y+SPACEBAR+1);

        arrow=new GUI_svg(rendu,0,0);
        arrow->DrawTriangle(10,10,1,"#fff",true,"#fff");

        SDL_Texture *tmp=SDL_CreateTexture(rendu,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,SPACEBAR/2,SPACEBAR/2);

        //==== [Button Vertical Up] =====
        btnVerticalUp=new GUI_button(rendu,tmp,getRect().x,getRect().y,Widget::CENTER,SPACEBAR,SPACEBAR);
        btnVerticalUp->getTextButton()->setTexture(arrow->getTexture());

        //==== [Button Vertical Down] ====
        btnVerticalDown=new GUI_button(rendu,tmp,getRect().x,getRect().y+getRect().h-SPACEBAR,Widget::CENTER,SPACEBAR,SPACEBAR);
        btnVerticalDown->getTextButton()->setTexture(arrow->getTexture());
        btnVerticalDown->getTextButton()->rotateFlip(180);

    }
    ~GUI_Scroll(){
        if(arrow!=NULL){
            delete arrow;
        }
        if(btnVerticalUp!=NULL){
            delete btnVerticalUp;
        }

        if(btnVerticalDown!=NULL){
            delete btnVerticalDown;
        }

    }

    void show(SDL_Renderer* rendu, SDL_Event& e, SDL_Texture* dtest=NULL)override{
        UpdateScroll();
        //===== Arrow Color ========//
        arrow->setColor(getBorderColor(getCurrentState()));

        //====== Button defilement vertical ======
        btn_vertical.scrollBtnVert.setFillColorState(-1,getBorderColor(getCurrentState()));

        //==== Affichage Des Buttons de Defilement =====

        //==[UP]===//
        btnVerticalUp->setBorderColorState(getCurrentState(),getBorderColor(getCurrentState()));
        btnVerticalUp->setFillColorState(getCurrentState(),getFillColor(getCurrentState()));

        //==[DOWN]===//
        btnVerticalDown->setBorderColorState(getCurrentState(),getBorderColor(getCurrentState()));
        btnVerticalDown->setFillColorState(getCurrentState(),getFillColor(getCurrentState()));

        if(btnVerticalUp->getCurrentState()==Widget::BTN_STAT_CLICKS){

            if(dstRect->y<oldRect.y){
                btn_vertical.scrollBtnVert.setPosition(btn_vertical.scrollBtnVert.getRect().x,btn_vertical.scrollBtnVert.getRect().y-1);
                dstRect->y+=velocity;
            }
        }
        if(btnVerticalDown->getCurrentState()==Widget::BTN_STAT_CLICKS){

            if(dstRect->y+dstRect->h>srcRect->h){
                btn_vertical.scrollBtnVert.setPosition(btn_vertical.scrollBtnVert.getRect().x,btn_vertical.scrollBtnVert.getRect().y+1);
                dstRect->y-=velocity;
            }
        }
        if(hasVertical){

            //=====  affichage rect vertical (affichage principale) ====
            GUI_Shape::show(rendu,e);

            btnVerticalUp->show(rendu,e,dtest);

            btnVerticalDown->show(rendu,e,dtest);

            //==[SCROLL VERTICALE BUTTON]===//
            btn_vertical.scrollBtnVert.show(rendu,e);
        }

    }
};


#endif // GUI_SCROLLBAR_H_INCLUDED
