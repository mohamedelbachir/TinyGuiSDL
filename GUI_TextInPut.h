#ifndef GUI_TEXTINPUT_H_INCLUDED
#define GUI_TEXTINPUT_H_INCLUDED
#include<vector>
#include"GUI_BordererTexture.h"
#define PADDINGTEXTRECT 10


class GUI_TextInput:public BorderTexture{
protected:

    std::vector<GUI_Texte*>talpha;

    SDL_Rect textEnter;

    SDL_Rect cursor;

    int max_lenght=0;

    int min_lenght=0;

    bool drawingShow=true;

    bool readOnly=false;

    TTF_Font *ft;

    int Textdirection=Widget::LEFT;

    std::string gTexte="";

    bool isPressed=false;

    bool isAlphabetic=false;

    Timer tput;

    Timer tcur;

    Timer tswap;

    SDL_Rect shapeText={0};

    bool once=false;

public:
    ///Constructeur de TextInput
    GUI_TextInput(SDL_Renderer *rendu,std::string pathfont,int taille,int x,int y,int direction=Widget::LEFT,int style=TTF_STYLE_NORMAL,int w=200,int h=40):BorderTexture(rendu,x,y,w,h){

        this->ID=W_TEXTE_INPUT;

        if(!TTF_WasInit()){
            TTF_Init();
        }

        ft=TTF_OpenFont(pathfont.c_str(),taille);


        TTF_SetFontStyle(ft,style);


        Textdirection=direction;

        //Variable Contenant la Position du Curseur
        cursor={PADDINGTEXTRECT,getRect().h/2-TTF_FontHeight(ft)/2,1,TTF_FontHeight(ft)};

         //Variable Rect Contenant espace occupe par les Textes afin de les affecter des Position {CENTER,LEFT,RIGHT}
        textEnter.w=0;

        textEnter.h=cursor.h;

        textEnter.x=cursor.x;

        textEnter.y=cursor.y;

        gRenderCpy=rendu;

        shapeText={cursor.x,0,w,h};

        shapeText.x=PADDINGTEXTRECT;
        std::cout<<"Initialisation Terniner !!!!"<<std::endl;

    }

    ///Destructeur
    ~GUI_TextInput(){
        std::cout<<"Suppression GUI_TextInput!!"<<std::endl;
        TTF_CloseFont(ft);
        clearText();
    }


    /**
        @brief GetTextInput
            fonction pour Obtenir la valeur du texte contenu
        @return : le Texte de sorti
    */
    std::string GetTextInput(){
        return gTexte;
    }

    /**
        @brief SetMaxLenght
        fonction permettant de fixer la longeur Max du Texte
        @param n:la taille a definir

    */
    void SetMaxLenght(int n){
        max_lenght=n;
    }

    /**
        @brief SetMinLenght
        fonction permettant de fixer la longeur min du Texte
        @param n:la taille a definir

    */
    void SetMinLenght(int n){
        min_lenght=n;
    }

    /**
        @brief : PutTextWithClear
            fonction ajouter du Text en effacent celui du Precedent
        @param : texte : le texte a ajouter
    */
    void PutTextWithClear(std::string texte){

        if(gTexte.length()-1<max_lenght||max_lenght==0){

            clearText();

            gTexte="";

            textEnter.w=0;

            char tc[2];

            for(int i=0;i<texte.length();i++){
                sprintf(tc,"%c",texte[i]);
                GUI_Texte *tmp=new GUI_Texte(gRenderCpy,ft,0,textEnter.y,tc);
                gTexte+=texte[i];
                textEnter.w+=tmp->getRect().w;
                talpha.push_back(tmp);

            }

            delete []tc;

        }else{

            if(!isPressed){

                PutTextWithClear(texte.substr(0,max_lenght));
            }
        }
    }

    /**
        @brief PutText
        fonction Permetant ajouter du Texte sans toute fois supprimer les autre contenu
        @param texte : texte a ajouter
    */
    void PutText(std::string texte){
        if(gTexte.length()-1<max_lenght||max_lenght==0){
            char tc[2];
            for(int i=0;i<texte.length();i++){
                sprintf(tc,"%c",texte[i]);
                GUI_Texte *tmp=new GUI_Texte(gRenderCpy,ft,0,textEnter.y,tc);
                gTexte+=texte[i];
                textEnter.w+=tmp->getRect().w;
                talpha.push_back(tmp);
            }

            delete []tc;

        }

     }


    void Update(SDL_Renderer *rendu,SDL_Event &e)override{

        /***/
        HandleInput(e);

        /***/
        StartToShow(rendu,e);

        /***/
        BorderTexture::EndToShow(rendu);

    }
    /**
        @brief : CheckWrite
        fonction permetant de capturer l'evenement de la souris lorsqu'elle se trouve dans le champs de souris
        et commencer la saisi
        @param event: l'event de Capture
    */
    bool CheckWrite(SDL_Event &event) {
        if(getCurrentState()==Widget::BTN_STAT_CLICKS&&!readOnly){
            isPressed=true;
        }else{
            if(OnGlobalMouseClicks(event)&&getCurrentState()!=Widget::BTN_STAT_HOVER&&!readOnly){
                isPressed=false;
            }
        }
        return isPressed;
    }

    void resizeShape(int w=-1, int h=-1)override{
        BorderTexture::resizeShape(w,h);
        if(w>0){
            shapeText.w=getRect().w;
        }
        if(h>0)
        {
            shapeText.h=getRect().h;
        }
    }


    void setcheckBoxPosition(GUI_CheckBox *bx)override{

       bx->getBoxCheck()->setPosition(PADDINGTEXTRECT,getRect().y+getRect().h/2-bx->getBoxCheck()->getRect().h/2);
       bx->UpdateRect();
       bx->setCheckWithLabel(false);
       if(!once){
           shapeText.x+=bx->getBoxCheck()->getRect().w+3;
           shapeText.w-=bx->getBoxCheck()->getRect().w+3;
           once=true;
       }
    }


    void HandleInput(SDL_Event& e)override{
        CheckWrite(e);
        switch(this->Textdirection){
            case LEFT:
                textEnter.x=shapeText.x;
                break;
            case CENTER:
                textEnter.x=shapeText.w/2-textEnter.w/2;
                break;
            case RIGHT:
                textEnter.x=shapeText.w-textEnter.w-PADDINGTEXTRECT;
                break;
        }

       switch(e.type)
       {
            case SDL_KEYDOWN:
                if(e.key.keysym.sym==SDLK_BACKSPACE&&tput.attendre(100)&&isPressed){

                    if(talpha.size()>0||gTexte.length()>0){
                        //Changement de Taille Pour Spacement du Texte
                        textEnter.w-=talpha[talpha.size()-1]->getRect().w;

                        //Suppression du Texture
                        talpha[talpha.size()-1]=nullptr;
                        delete talpha[talpha.size()-1];


                        //Supression dans le Texte String
                        gTexte.erase(gTexte.length()-1,gTexte.length());

                        //Suppression dans le Tableau dynamique
                        talpha.pop_back();

                    }
                }
                if(e.key.keysym.sym==SDLK_RETURN){
                    std::cout<<gTexte<<std::endl;
                }
                break;

            case SDL_TEXTINPUT:
                   char* caractere=e.text.text;
                   if(tput.attendre(150)&&isPressed){
                        if(!isAlphabetic){
                                PutText(caractere);
                        }else{
                            if((caractere[0]>=65&&caractere[0]<=90)||(caractere[0]>=97&&caractere[0]<=122)){
                                PutText(caractere);
                            }else{
                               //beep(2000,50);
                            }
                            break;
                        }
                   }
            break;
        }
      cursor.x=textEnter.x+textEnter.w;
    }

    void StartToShow(SDL_Renderer *rendu,SDL_Event e){
        static bool showCur=true;
        int k=0;
        for(int i=0;i<talpha.size();i++){
            talpha[i]->setPosition(textEnter.x+k,talpha[i]->getRect().y);
            k+=talpha[i]->getRect().w;
        }
        BorderTexture::StartToShow(rendu,e);
            for(int i=0;i<talpha.size();i++){
                talpha[i]->show(rendu,e);
            }
            if(isPressed){
                if(showCur){
                    DrawRenderColor(rendu,gBorderColor);
                    SDL_RenderFillRect(rendu,&cursor);
                }
                if(tcur.attendre(500)){
                    showCur=!showCur;
                }
            }
    }
    void clearText(){
        for(int i=talpha.size()-1;i>0;i--){
            talpha[i]=nullptr;
            delete talpha[i];
            talpha.pop_back();
        }
        talpha.clear();
    }


    void setFillColorState(int state, SDL_Color col)override{

    }

    void AddWidgets(GUI_Texte *t){
        talpha.push_back(t);
    }

    /***/
    void SetPaddingX(int w){
        gTargetCursor.w-=w;
        shapeText.w-=w;
    }

    /***/
    void setAlphabetic(bool enable){
        isAlphabetic=enable;

    }

    /***/
    void setReadOnly(bool enable)
    {
        readOnly=enable;
    }

};


#endif // GUI_TEXTINPUT_H_INCLUDED
