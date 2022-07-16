#ifndef GUI_TEXTURE_H_INCLUDED
#define GUI_TEXTURE_H_INCLUDED
#include"Widget.h"
#include "GUI_CheckBox.h"
class GUI_Texture:public Widget,public GUI_CheckBox{
protected:

    ///Variable Permettant de tourner (Flipper) la Texture
    SDL_RendererFlip gFlip=SDL_FLIP_NONE;

    ///Angle de Rotation de la Texture
    double gAngle=0;

    ///Texture Affichage
    SDL_Texture *gTexture;

    /// Source Rect de la Texture
    SDL_Rect gSrcRect={0,0,getRect().w,getRect().h};

    /// Centre de la Texture
    SDL_Point gCenter={getRect().w/2,getRect().h/2};

public:

    /**
        @brief ~GUI_Texture
           Destructeur de Texture en Liberant les espaces
    */
    virtual ~GUI_Texture(){
        if(gTexture!=nullptr){
            gTexture=NULL;
            SDL_DestroyTexture(gTexture);
        }
        std::cout<<"Suppression GUI_Texture!!!"<<std::endl;
    }

    /**
        @brief UpdateSizeTexture
          Mise a jour la taille du Texture
    */
    void UpdateSizeTexture(){
        if(gTexture!=NULL){
            SDL_QueryTexture(gTexture,NULL,NULL,&gRect.w,&gRect.h);
        }
        UpdateSizeOfSrc();

        //misa jour position
        updateSizePosition();
    }

    /**
        @brief UpdateSizeOfSrc
        fonction permettant de mettre a jour la source,centre,...
    */
    void UpdateSizeOfSrc(){
        gSrcRect.w=gRect.w;
        gSrcRect.h=gRect.h;
        gCenter.x=gRect.w/2;
        gCenter.y=gRect.h/2;
    }

    /**
        @brief resize
          Fonction Permettant de Changer la taille de la Texture
        @param (w,h) : nouvelle Hauteur et Largeur ,par defaut -1 si inchanger
    */
    virtual void resize(int w=-1,int h=-1){
        if(h>=0){
            gRect.h=h;
        }
        if(w>=0){
            gRect.w=w;
        }
        updateSizePosition();

    }

    /**
        @brief rotateFlip
        fonction d'effectuer une rptation d'une texture
        @param angle: angle de rotation
        @param flip: flippage de texture sur (oui || non) =>non
    */
    void rotateFlip(double angle,SDL_RendererFlip flip=SDL_FLIP_NONE){
        this->gAngle=angle;
        this->gFlip=flip;
    }

    /**
        @brief setTexture
          Fonction Permettant de Changer la Texture
        @param texture : Texture a changer
    */
    void setTexture(SDL_Texture *texture){
        if(texture!=nullptr){
            gTexture=texture;
        }
        UpdateSizeTexture();

    }

    /**
        @brief getTexture
          Fonction Permettant d'obtenir la Texture
        @return  Texture renvoiyer
    */
    SDL_Texture *getTexture(){
        return gTexture;
    }

    /**
        @brief show
        Affichage de la texture
        @param rendu:Rendu Affichage
        @param e:Evenement de Capture

    */
    void show(SDL_Renderer *rendu,SDL_Event &e,SDL_Texture *dtest=NULL)override{
        ///capture des evenement
        if(IsCheckMouseEvent()){
            CheckEventMouse(e);
        }

        ///mis a jour de la texture
        if(SDL_RenderTargetSupported(rendu)==SDL_TRUE){
           if(dtest!=NULL)SDL_SetRenderTarget(rendu,NULL);
           Update(rendu,e);
           if(dtest!=NULL){
                SDL_SetRenderTarget(rendu,dtest);
           }
        }else{
           Update(rendu,e);
        }

        ///affichage de la texture
        if(getDisplay()){
            if(gTexture!=nullptr){
                if(ID==W_TEXTE){
                    SDL_SetTextureColorMod(gTexture,getFillColor(getCurrentState()).r,getFillColor(getCurrentState()).g,getFillColor(getCurrentState()).b);
                }
                SDL_RenderCopyEx(rendu,gTexture,&gSrcRect,&gRect,gAngle,&gCenter,gFlip);
            }
        }

        ///affichage du checkBox Si visible
        if(checkVisibility){
            showCheck(rendu,e,this);
        }

        //affichage de couleur de deboggage
        if(ColorShape){

            //cas des couleur de Bordure
            DrawRenderColor(rendu,gColorShape);
            SDL_RenderDrawRect(rendu,&gRect);

            //cas de couleur de gestion Event
            DrawRenderColor(rendu,gColorEvent);
            SDL_RenderDrawRect(rendu,&gTargetCursor);

        }
    }
    void setcheckBoxPosition(GUI_CheckBox *bx)override{
        if(!once){
            setPosition(bx->getBoxCheck()->getRect().x+bx->getBoxCheck()->getRect().w+3,bx->getBoxCheck()->getRect().y+bx->getBoxCheck()->getRect().h/2-getRect().h/2);
        }
    }
};
#endif // GUI_TEXTURE_H_INCLUDED
