#ifndef GUI_BORDERERTEXTURE_H_INCLUDED
#define GUI_BORDERERTEXTURE_H_INCLUDED
#include<memory>
#include<vector>
class BorderTexture:public GUI_Texture{

protected:

    ///Rect du BorderTexture
    SDL_Rect rectBorder;

    ///Image Du BorderTexture
    GUI_Image *borderImg;

    SDL_Rect clipSrc={0};

    bool retractW=false;
    bool retractH=false;

private:
    void init(int w,int h){

       if(w>0&&h>0){

            if(gTexture!=nullptr){
                gTexture=nullptr;
                SDL_DestroyTexture(gTexture);
            }

            //=== Creation de la Texture Target ======
            gTexture=SDL_CreateTexture(gRenderCpy,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,w,h);

            if(gTexture==nullptr){
                std::cout<<"Imposible de creer la Texture(BorderTexture) ........."<<std::endl;
                std::cout<<"erreur "<<SDL_GetError();
                exit(EXIT_FAILURE);
            }

            //=== Bordure de TargetTexture ===//
            rectBorder.w=w;
            rectBorder.h=h;

            //==Mis a jour de la Taille du texture et autre
            UpdateSizeTexture();

            //mis a jour des condition de Retartion
            if(retractW){
                //resize(0,-1);
            }

            if(retractH){
                //resize(-1,0);
            }
            clipSrc=rectBorder;
        }
    }

public:

    ///Constructeur par defaut
    BorderTexture(){
        /*definition de ID*/
        ID=W_BORDER_TEXTURE;
        clipSrc={0};
        rectBorder={0};
    }

    /**
        @brief BorderTexture
        constructeur de Border Texture

        @param rendu:rendu affichage
        @param (x,y):position de destination
        @param (w,h):taille de la texture
        @param (retarctW):booleen pour reduire en largeur//par defaut non
        @param (retarctH):booleen pour reduire en hauteur//par defaut non
    */
    BorderTexture(SDL_Renderer *rendu,int x,int y,int w,int h,bool retractW=false,bool retractH=false){
        /*definition de ID*/
        ID=W_BORDER_TEXTURE;

        //=== Initialisation de la position
        gRect.x=x;
        gRect.y=y;

        //=== Bordure de TargetTexture ===//
        rectBorder.x=0;
        rectBorder.y=0;

        //Definition de Couleur de bordure/fill par defaut,clicks,Hover
        gDefaultBorderColor=gClicksBorderColor=gHoverBorderColor={0,0,0,255};
        gDefaultFillColor=gClicksFillColor=gHoverFillColor={255,255,255,255};

        //mis a jour des condition de Retartion
        this->retractW=retractW;
        this->retractH=retractH;

        gRenderCpy=rendu;

        init(w,h);
    }

    ///Destructeur de Border
    ~BorderTexture(){
        if(borderImg!=nullptr){
            borderImg=nullptr;
            delete borderImg;
        }
    }

    /**
        @brief StartToShow
        fonction permettant de Commencer le dessin dans le Target Texture en tantque Rendu
        @param rendu:Rendu d'affichage
        @param event:Capture d'evenement
    */
    void StartToShow(SDL_Renderer *rendu,SDL_Event event){
        SDL_SetRenderTarget(rendu, gTexture);
            //Couleur de remplissage de la Bordeless Texture
            DrawRenderColor(rendu,gFillColor);
            SDL_RenderFillRect(rendu,NULL);
            SDL_RenderClear(rendu);

            SDL_RenderSetClipRect(rendu,&clipSrc);
            SDL_RenderSetLogicalSize(rendu,clipSrc.w,clipSrc.h);

    }

    /**
        @brief EndToShow
        fonction permettant d'arreter le dessin dans le Target Texture en tantque Rendu
        @param rendu:Rendu d'affichage
    */
    void EndToShow(SDL_Renderer *rendu){
         //std::cout<<"\nend";
            // Couleur de Bordure
            DrawRenderColor(rendu,gBorderColor);
            SDL_RenderDrawRect(rendu,&rectBorder);

        //in du targetTexture
        SDL_SetRenderTarget(rendu,NULL);

        //Mettre de la Transparence
        SDL_SetTextureBlendMode(gTexture,SDL_BLENDMODE_BLEND);
        if(!getDisplay()){
            SetCheckMouseEvent(false);
        }else{
            SetCheckMouseEvent(true);
        }
    }

    /**
        @brief CloseBorderTexture
        fonction permettant la fermeture de la Border texture cas d'une animation
        @param animId (type animation)
    */
    void CloseBorderTexture(int animId=0){
        switch(animId){
            case 0:
                //if(gRect.h>0){
                  //  resize(-1,getRect().h-VELOCITY);
               // }else{
                    SetDisplay(false);
                //}
                break;

        }
    }

    /**
        @brief OpenBorderTexture
        fonction permettant l'ouverture de la borderTexture cas d'une animation
        @param animId (type animation)
    */
    void OpenBorderTexture(int animId=0){
        SetDisplay(true);
        switch(animId){
            case 0:
                //if(gRect.h<rectBorder.h){
                  //  resize(-1,getRect().h+VELOCITY);
                //}
                break;
        }
    }

    /*void Update(SDL_Renderer* rendu, SDL_Event& e)override{
        StartToShow(rendu,e);
        EndToShow(rendu);
    }*/

    void resizeShape(int w=-1,int h=-1)override{
        if(h>=0){
            setHeight(h);
        }
        if(w>=0){
            setWidth(w);
        }
    }
    void setWidth(int w){
        init(w,rectBorder.h);
    }
    void addWidth(int w){
        init(rectBorder.w+w,rectBorder.h);
    }
    void setHeight(int h){
        init(rectBorder.w,h);
    }
    void addHeight(int h){
        init(rectBorder.w,rectBorder.h+h);
    }

};
#endif // GUI_BORDERERTEXTURE_H_INCLUDED
